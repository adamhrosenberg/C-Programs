#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <elf.h>
#include <string.h>

/* Given the in-memory ELF header pointer as `ehdr` and a section
   header pointer as `shdr`, returns a pointer to the memory that
   contains the in-memory content of the section */
#define AT_SEC(ehdr, shdr) ((void *)(ehdr) + (shdr)->sh_offset)

static void check_for_shared_object(Elf64_Ehdr *ehdr);
static void fail(char *reason, int err_code);
int i;

Elf64_Shdr *section_by_name(Elf64_Ehdr *ehdr, char *name){
  Elf64_Shdr *shdrs = (void*)ehdr+ehdr->e_shoff;
  char *strs = (void*)ehdr+shdrs[ehdr->e_shstrndx].sh_offset;

  for(; i < ehdr->e_shnum; i++){
   if(strcmp(name,strs + shdrs[i].sh_name) == 0){
     Elf64_Shdr *section = &shdrs[i];
     return section;	
    }
  }
  return 0;
}

Elf64_Shdr *section_by_index(Elf64_Ehdr *ehdr, int idx){
	Elf64_Shdr *shdrs = (void*)ehdr+ehdr->e_shoff;
    Elf64_Shdr *section = &shdrs[idx];
    return section;
}


unsigned long process_near_jump(char * functionptr){
	unsigned long offset = 0;
	unsigned char togo = 0;

	togo = *(functionptr+3);
	offset |= togo;
	offset = offset << 8;

	togo = *(functionptr+2);
	offset |= togo;
	offset = offset << 8;

	togo = *(functionptr+1);
	offset |= togo;
	offset = offset << 8;

	togo = *(functionptr);
	offset |= togo;

	return offset;
}

void byte_seq(Elf64_Ehdr *ehdr, char* functionptr, char* strs, Elf64_Sym* syms){
	int found = 0;
	//printf("in byteseq");
	//printf("in byte seq");
	Elf64_Shdr *rela_dyn_shdr = section_by_name(ehdr, ".rela.dyn");
	Elf64_Rela *relas = AT_SEC(ehdr, rela_dyn_shdr);

	int add;
	unsigned long offset = 0;
	for (add = 0; add < 7; add++){
		unsigned long togo = *(functionptr + add);
		if(add>=3){
			togo = togo<<((add-3)<<3);
			offset |= togo;
		}
	}
	offset += 0x7 + (unsigned long)functionptr;
	offset = offset & 0xff;
	//printf("off: %0x\n", offset);
	int j, relcount = rela_dyn_shdr->sh_size / sizeof(Elf64_Rela);
	//printf("%d\n", relcount);
	int symbol_index=0;
	for(j=0;j<relcount; j++){
		unsigned long localoffset = relas[j].r_offset & 0xff;
		//printf("%0x %0x\n", offset, localoffset);
		if(localoffset == offset& 0xff){
			symbol_index = ELF64_R_SYM(relas[j].r_info);
			found = 1;
		}
	}
	char * var_name = strs + syms[symbol_index].st_name;
	printf("  %s\n", var_name);
}

int main(int argc, char **argv) {
  int fd;
  size_t len;
  void *p;
  Elf64_Ehdr *ehdr;

  if (argc != 2)
    fail("expected one file on the command line", 0);

  /* Open the shared-library file */
  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    fail("could not open file", errno);

  /* Find out how big the file is: */
  len = lseek(fd, 0, SEEK_END);

  /* Map the whole file into memory: */
  p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == (void*)-1)
    fail("mmap failed", errno);

  /* Since the ELF file starts with an ELF header, the in-memory image
     can be cast to a `Elf64_Ehdr *` to inspect it: */
  ehdr = (Elf64_Ehdr *)p;

  /* Check that we have the right kind of file: */
  check_for_shared_object(ehdr);

  /* Add a call to your work here */

  	Elf64_Shdr *dynsym_shdr = section_by_name(ehdr, ".dynsym");
	Elf64_Sym *syms = AT_SEC(ehdr, dynsym_shdr);
	char *strs = AT_SEC(ehdr, section_by_name(ehdr, ".dynstr"));
	int i,j, count = dynsym_shdr->sh_size / sizeof(Elf64_Sym);
	for(i = 0; i < count; i++){
		if(ELF64_ST_TYPE(syms[i].st_info) == STT_FUNC){
			char* symstring = strs+syms[i].st_name;
			if(!(symstring[0] == '_')){
				printf("%s\n", strs + syms[i].st_name);
				Elf64_Shdr *shdr = section_by_index(ehdr, syms[i].st_shndx);
				char *functionptr = AT_SEC(ehdr, shdr) + (syms[i].st_value - shdr->sh_addr);
				char *first_byte = (functionptr);
				char *second_byte = (functionptr+1);
				//printf("first byte: %0x | second byte: %0x \n", *first_byte, *second_byte);
				while((*first_byte & 0xff) != 0xc3){
					unsigned char first = (*first_byte&0xff);
					unsigned char second = (*second_byte&0xff);
					if((first == 0x48) && (second == 0x8b)){
						byte_seq(ehdr, first_byte, strs, syms);
						first_byte += 7;
						second_byte += 7;
					}
					else if(first == 0xeb){
						break;
					}
					else if((first == 0x63 || first == 0x89 || first == 0x8b)&&(second == 0xc0)){
						first_byte++;
						second_byte++;
					}
					else if(first == 0x48 && (second == 0x63 || second == 0x89 || second == 0x8b)){
						char third_val = (*(second_byte +1)&0xff);
						if(third_val&&0xc0 == 0xc0){
							first_byte+=3;
							second_byte+=3;
						}else{
							first_byte++;
							second_byte++;
						}
					}
					else if((*first_byte&0xff) == 0xe9 ){
						break; //was not able to get the code below to work.
//						char * newptr = first_byte + 1;
//						int offset = (int)process_near_jump(newptr);
//						char* new_addy = offset + 0x7 + first_byte;
//						unsigned int finoff = (unsigned int)process_near_jump(new_addy);
//						unsigned long total =  finoff + new_addy+0x4;
//						total = total & 0xfff;
//
//						unsigned long funcoffset = 0;
//						Elf64_Shdr *rela_dyn_shdr = section_by_name(ehdr, ".rela.plt");
//						Elf64_Rela *relas = AT_SEC(ehdr, rela_dyn_shdr);
//						int i, count = rela_dyn_shdr->sh_size / sizeof(Elf64_Rela);
//						for (i = 0; i < count; i++) {
//						 //printf("%d\n", ELF64_R_SYM(relas[i].r_info));
//							unsigned long tofind = relas[i].r_offset & 0xfff;
//							//printf("%0x %0x\n", tofind, total);
//							if(total == tofind){
//								//printf("in here\n");
//								funcoffset = ELF64_R_SYM(relas[i].r_info);
//								char * funcname = strs + syms[funcoffset].st_name;
//								printf(" (%s)\n", funcname);
//							}
//						}
//						first_byte +=5;
//						second_byte+=5;

					}else{
						first_byte = first_byte + 1;
						second_byte++;
					}
					//printf("first byte: %0x | second byte: %0x \n", *first_byte, *second_byte);
				}
			}
		}
	}
	//printf("EOF");
  return 0;
}


static void check_for_shared_object(Elf64_Ehdr *ehdr) {
  if ((ehdr->e_ident[EI_MAG0] != ELFMAG0)
      || (ehdr->e_ident[EI_MAG1] != ELFMAG1)
      || (ehdr->e_ident[EI_MAG2] != ELFMAG2)
      || (ehdr->e_ident[EI_MAG3] != ELFMAG3))
    fail("not an ELF file", 0);

  if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
    fail("not a 64-bit ELF file", 0);
  
  if (ehdr->e_type != ET_DYN)
    fail("not a shared-object file", 0);
}

static void fail(char *reason, int err_code) {
  fprintf(stderr, "%s (%d)\n", reason, err_code);
  exit(1);
}


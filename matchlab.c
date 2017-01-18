#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adam rosenberg
// Objective here is to recognize some regular expressions

int aflag = 0;
int bflag = 0;
int cflag = 0;
int tflag = 0;


void doaflag(char buffer[]){

/**
 * a flag
 *
 * between 4 and 5 repetitions (inclusive) of the letter “k”;
3 or more repetitions of the letter “v”; and
an odd number of uppercase letters.
 */

    const int length = strlen(buffer);
    int kcount = 0; //k = 107
    int vcount = 0;  //v = 188
    int uppercount = 0; //capitol is 65-90
    int othercount = 0;
    int order = 1;
    int i;
    for(i = 0; i < length; i ++){
        if(buffer[i] == 107){
            kcount++;
        }else if(buffer[i] == 118){
            vcount++;
        }else if(buffer[i] <= 90 && buffer[i] >=65){
            uppercount++;
        }else{
            othercount++;
        }
    }

    if(buffer[0] != 'k')
        order = 0;
    if(buffer[4] == 'k' && !(buffer[5] == 'v'))
        order = 0;
    if(buffer[3] == 'k' && !(buffer[4] == 'v'))
       order = 0;
    if(!(buffer[vcount+kcount] >= 'A' && buffer[vcount+kcount] <= 'Z'))
        order = 0;


    if((kcount == 4 || kcount == 5) && vcount >=3 && ((uppercount&1)==1) && othercount == 0 && order){

        if(tflag){
            char first = buffer[0];
            for(i = 0; i < length; i++){
                buffer[i] = first;
                //if t flag...print.
                printf("%c", buffer[i]);
            }
            printf("\n");
        }else{
            printf("yes\n");
        }
    }
    else{

        if(!tflag){
            printf("no\n");
        }
    }
}
void dobflag(char buffer[]){

    /**
     *  any even number (including zero) repetitions of the letter “h”;
        between 1 and 3 (inclusive) decimal digits — call this sequence X;
        between 3 and 6 repetitions (inclusive) of the letter “n”;
        the same character sequence as X, but reversed; and
        an odd number of uppercase letters.
            For matches, perform the following conversion:
            add one “E” before each “G”.
     */
    const int length = strlen(buffer);
    int order = 1;
    int hcount = 0; //h = 104
    int deccount = 0; // 48-57 is a num 0-9
    int numbers[6];
    int ncount = 0; //n = 110
    int isdecreversed = 0; //0 false 1 true
    int uppercount = 0; //upper is 65-90
    int othercount=0;

    int i;
    for (i = 0; i < length; i++) {
        if (buffer[i] == 104) {
            hcount++;
        } else if (buffer[i] == 110) {
            ncount++;
        } else if (buffer[i] <= 90 && buffer[i] >= 65) {
            uppercount++;
        } else if (buffer[i] >= 48 && buffer[i] <= 57) {

            if(deccount < 6){
                numbers[deccount] = buffer[i];
            }
            deccount++;
            //add constraint..maybe? lol.
        }else{
            othercount++;
        }
    }

    if(hcount == 0 && !(buffer[0]>= 48 && buffer[0] <= 57 )){
        order = 0;
    }
    if(!(buffer[length-1] >= 'A' && buffer[length-1] <= 'Z'))
        order = 0;


    if (deccount == 2) {
        if(buffer[hcount+1]!='n')
            order = 0;
        if (numbers[0] == numbers[1])
            isdecreversed = 1;
    } else if (deccount == 4) {
        if(buffer[hcount+2] != 'n')
            order = 0;
        if (numbers[0] == numbers[3] && numbers[1] == numbers[2])
            isdecreversed = 1;
    } else if (deccount == 6) {
        if(buffer[hcount + 3] != 'n')
            order = 0;
        if (numbers[0] == numbers[5] && numbers[1] == numbers[4] && numbers[2] == numbers[3])
            isdecreversed = 1;
    } else {
        isdecreversed = 0;
    }

//    printf("is reversed %d, h count %d, n count %d, uppercount %d, othercount %d, deccount %d, order %d \n", isdecreversed, hcount, ncount, uppercount, othercount, deccount, order);

    if((isdecreversed == 1) && (hcount%2==0 || hcount == 0) && (ncount > 2 && ncount < 7) && (uppercount%2 == 1) && othercount==0 && order ){
        int extra = 0;

        if(tflag){
            for(i = 0 ; i < length+extra; i++){
                if(buffer[i] == 71){
                    printf("E");
                }
                printf("%c", buffer[i]);
            }
            printf("\n");
        }else{
            printf("yes\n");
        }
    }else{
        if(!tflag){
            printf("no\n");
        }
    }
}
void docflag(char buffer[]){

    /**
     *  any odd number of repetitions of the letter “a”;
        between 1 and 3 (inclusive) decimal digits — call this sequence X;
        any odd number of repetitions of the letter “y”;
        an odd number of uppercase letters; and
        the same characters as the odd-positioned characters in X.

        For matches, perform the following conversion:
        remove every “C” and “G”.
     */
    const int length = strlen(buffer);
    int acount = 0; // 97
    int deccount = 0; //48-57
    int ycount = 0; //121
    int uppercount = 0; //65-90
    int numbers[5];
    int othercount = 0;
    int isdecodd=0;
    int startsatodd = 0;
    int order = 1;

    int i;
    for (i = 0; i < length; i++) {
        if (buffer[i] == 97) {
            acount++;
        } else if (buffer[i] == 121) {
            ycount++;
        } else if (buffer[i] <= 90 && buffer[i] >= 65) {
            uppercount++;
        } else if (buffer[i] >= 48 && buffer[i] <= 57) {
            if(deccount < 5){
                numbers[deccount] = buffer[i];
//                printf("deccount = %d, numbers[deccount] = %d, buffer[%d] = %d\n", deccount, numbers[deccount], i, buffer[i]);
                deccount++;
            }
        }else{
            othercount++;
        }
    }


    /**
*  any odd number of repetitions of the letter “a”;
   between 1 and 3 (inclusive) decimal digits — call this sequence X;
   any odd number of repetitions of the letter “y”;
   an odd number of uppercase letters; and
   the same characters as the odd-positioned characters in X.

   For matches, perform the following conversion:
   remove every “C” and “G”.
*/

    if(buffer[0] != 'a'){
        order = 0;
    }
    if(!(buffer[acount] >= 48 && buffer[acount] <= 57))
        order = 0;

    if(!(buffer[length-1] >= 48 && buffer[length-1] <= 57))
        order = 0;


    for(i = 0 ; i < 5; i++) {
        if (deccount == 2) { //len 1
            isdecodd = 0;
        } else if (deccount == 3) { //len 2
            if (numbers[1] == numbers[2]){
                isdecodd = 1;
            }
        } else if (deccount == 4) { //len 3
            if (numbers[1] == numbers[3])
                isdecodd = 1;
        } else {
            isdecodd = 0;
        }

    }


//        printf("is odd %d, a count %d, y count %d, uppercount %d, othercount %d, deccount %d \n", isdecodd, acount,
//               ycount, uppercount, othercount, deccount);
    if ((acount & 1) == 1 && isdecodd == 1 && ((ycount & 1) == 1) && (uppercount & 1) == 1 && othercount == 0 && order) {
        if(tflag){
            for(i =0; i < length; i++){
                if(buffer[i] != 'C' && buffer[i] != 'G')
                    printf("%c", buffer[i]);
            }
            printf("\n");
        }
        else{
            printf("yes\n");
        }
        //adapt this for odd positions of x...
    } else {
        if(tflag){

        }else{
            printf("no\n");
        }
    }

}


//driver method to call the correct methods for each string. (char array)
void dowork(char buffer[]){
    const int length = strlen(buffer);

    if(aflag)
        doaflag(buffer);
    else if(bflag)
        dobflag(buffer);
    else if(cflag)
        docflag(buffer);
    else{
        doaflag(buffer);
    }
}


//main method. parses for flags, then passes each 'string' to a driver method that calls the right method based on active flags.
int main (int argc, char *argv[])
{
    int count = 0;

    char buffer[100]; //malloc
    int i;
    for(i = 0; i < 100; i ++){
        buffer[i]=' ';
    }

//    //searching for a dash and finding the flags after that..
    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){ //str[0] = argv...
            char argument = argv[i][1];
                switch (argument) {
                    case 'a':
                        aflag = 1;
                        break;
                    case 'b':
                        bflag = 1;
                        break;
                    case 'c':
                        cflag = 1;
                        break;
                    case 't':
                        tflag = 1;
                        break;
                }
        }else{
            dowork(argv[i]); //pass each element of buffer call alg here
        }
    }
    return 0;
}


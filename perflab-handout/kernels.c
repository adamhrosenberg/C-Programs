/*******************************************
 * Solutions for the CS:APP Performance Lab
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */

student_t student = {
  "Adam Rosenberg",     /* Full name */
  "u0751643@utah.edu",  /* Email address */

};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_pinwheel - The naive baseline version of pinwheel 
 */
char naive_pinwheel_descr[] = "naive_pinwheel: Naive baseline implementation";
void naive_pinwheel(int dim, pixel *src, pixel *dest)
{
  int i, j;

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim/2 - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
    
  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim/2 - 1 - j, dim/2 + i, dim)] = src[RIDX(i, dim/2 + j, dim)];

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim - 1 - j, i, dim)] = src[RIDX(dim/2 + i, j, dim)];

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim - 1 - j, dim/2 + i, dim)] = src[RIDX(dim/2 + i, dim/2 + j, dim)];
}

/* 
 * MINE!!!! BELOW
 * rotate - Your current working version of pinwheel
 * IMPORTANT: This is the version you will be graded on
 */
char pinwheel_descr[] = "pinwheel: Current working version";
void pinwheel(int dim, pixel *src, pixel *dest)
{
  int i, j;
  int halfdim = dim>>1;
  int firstindex;


//////first
  for (i = 0; i < halfdim; i+=16)
    for (j = 0; j < halfdim; j++){
      firstindex = halfdim - 1 - j;
      dest[RIDX(firstindex, i, dim)] = src[RIDX(i, j, dim)];
      dest[RIDX(firstindex, i+1, dim)] = src[RIDX(i+1, j, dim)];
      dest[RIDX(firstindex, i+2, dim)] = src[RIDX(i+2, j, dim)];
      dest[RIDX(firstindex, i+3, dim)] = src[RIDX(i+3, j, dim)];
      dest[RIDX(firstindex, i+4, dim)] = src[RIDX(i+4, j, dim)];
      dest[RIDX(firstindex, i+5, dim)] = src[RIDX(i+5, j, dim)];
      dest[RIDX(firstindex, i+6, dim)] = src[RIDX(i+6, j, dim)];
      dest[RIDX(firstindex, i+7, dim)] = src[RIDX(i+7, j, dim)];
      dest[RIDX(firstindex, i+8, dim)] = src[RIDX(i+8, j, dim)];
      dest[RIDX(firstindex, i+9, dim)] = src[RIDX(i+9, j, dim)];
      dest[RIDX(firstindex, i+10, dim)] = src[RIDX(i+10, j, dim)];
      dest[RIDX(firstindex, i+11, dim)] = src[RIDX(i+11, j, dim)];
      dest[RIDX(firstindex, i+12, dim)] = src[RIDX(i+12, j, dim)];
      dest[RIDX(firstindex, i+13, dim)] = src[RIDX(i+13, j, dim)];
      dest[RIDX(firstindex, i+14, dim)] = src[RIDX(i+14, j, dim)];
      dest[RIDX(firstindex, i+15, dim)] = src[RIDX(i+15, j, dim)];
  }


///////second
  for (i = 0; i < halfdim; i+=16)
    for (j = 0; j < halfdim; j++){
      //dest[RIDX(dim/2 - 1 - j, dim/2 + i, dim)] = src[RIDX(i, dim/2 + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i, dim)] = src[RIDX(i, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+1, dim)] = src[RIDX(i+1, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+2, dim)] = src[RIDX(i+2, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+3, dim)] = src[RIDX(i+3, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+4, dim)] = src[RIDX(i+4, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+5, dim)] = src[RIDX(i+5, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+6, dim)] = src[RIDX(i+6, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+7, dim)] = src[RIDX(i+7, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+8, dim)] = src[RIDX(i+8, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+9, dim)] = src[RIDX(i+9, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+10, dim)] = src[RIDX(i+10, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+11, dim)] = src[RIDX(i+11, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+12, dim)] = src[RIDX(i+12, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+13, dim)] = src[RIDX(i+13, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+14, dim)] = src[RIDX(i+14, halfdim + j, dim)];
      dest[RIDX(halfdim - 1 - j, halfdim + i+15, dim)] = src[RIDX(i+15, halfdim + j, dim)];
   }



////////////third
  for (i = 0; i < halfdim; i+=16)
    for (j = 0; j < halfdim; j++){
      //dest[RIDX(dim - 1 - j, i, dim)] = src[RIDX(dim/2 + i, j, dim)];
      dest[RIDX(dim - 1 - j, i, dim)] = src[RIDX(halfdim + i, j, dim)];
      dest[RIDX(dim - 1 - j, i+1, dim)] = src[RIDX(halfdim + i+1, j, dim)];
      dest[RIDX(dim - 1 - j, i+2, dim)] = src[RIDX(halfdim + i+2, j, dim)];
      dest[RIDX(dim - 1 - j, i+3, dim)] = src[RIDX(halfdim + i+3, j, dim)];
      dest[RIDX(dim - 1 - j, i+4, dim)] = src[RIDX(halfdim + i+4, j, dim)];
      dest[RIDX(dim - 1 - j, i+5, dim)] = src[RIDX(halfdim + i+5, j, dim)];
      dest[RIDX(dim - 1 - j, i+6, dim)] = src[RIDX(halfdim + i+6, j, dim)];
      dest[RIDX(dim - 1 - j, i+7, dim)] = src[RIDX(halfdim + i+7, j, dim)];
      dest[RIDX(dim - 1 - j, i+8, dim)] = src[RIDX(halfdim + i+8, j, dim)];
      dest[RIDX(dim - 1 - j, i+9, dim)] = src[RIDX(halfdim + i+9, j, dim)];
      dest[RIDX(dim - 1 - j, i+10, dim)] = src[RIDX(halfdim + i+10, j, dim)];
      dest[RIDX(dim - 1 - j, i+11, dim)] = src[RIDX(halfdim + i+11, j, dim)];
      dest[RIDX(dim - 1 - j, i+12, dim)] = src[RIDX(halfdim + i+12, j, dim)];
      dest[RIDX(dim - 1 - j, i+13, dim)] = src[RIDX(halfdim + i+13, j, dim)];
      dest[RIDX(dim - 1 - j, i+14, dim)] = src[RIDX(halfdim + i+14, j, dim)];
      dest[RIDX(dim - 1 - j, i+15, dim)] = src[RIDX(halfdim + i+15, j, dim)];
    }

/////fourth
  for (i = 0; i < halfdim; i+=16)
    for (j = 0; j < halfdim; j++){
      //dest[RIDX(dim - 1 - j, dim/2 + i, dim)] = src[RIDX(dim/2 + i, dim/2 + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i, dim)] = src[RIDX(halfdim + i, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+1, dim)] = src[RIDX(halfdim + i+1, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+2, dim)] = src[RIDX(halfdim + i+2, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+3, dim)] = src[RIDX(halfdim + i+3, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+4, dim)] = src[RIDX(halfdim + i+4, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+5, dim)] = src[RIDX(halfdim + i+5, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+6, dim)] = src[RIDX(halfdim + i+6, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+7, dim)] = src[RIDX(halfdim + i+7, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+8, dim)] = src[RIDX(halfdim + i+8, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+9, dim)] = src[RIDX(halfdim + i+9, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+10, dim)] = src[RIDX(halfdim + i+10, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+11, dim)] = src[RIDX(halfdim + i+11, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+12, dim)] = src[RIDX(halfdim + i+12, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+13, dim)] = src[RIDX(halfdim + i+13, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+14, dim)] = src[RIDX(halfdim + i+14, halfdim + j, dim)];
      dest[RIDX(dim - 1 - j, halfdim + i+15, dim)] = src[RIDX(halfdim + i+15, halfdim + j, dim)];
    }
}

/*********************************************************************
 * register_pinwheel_functions - Register all of your different versions
 *     of the pinwheel kernel with the driver by calling the
 *     add_pinwheel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_pinwheel_functions() {
  add_pinwheel_function(&pinwheel, pinwheel_descr);
  add_pinwheel_function(&naive_pinwheel, naive_pinwheel_descr);
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
  return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_weighted_sum(pixel_sum *sum, pixel p, double weight) 
{
  sum->red += (int) p.red * weight;
  sum->green += (int) p.green * weight;
  sum->blue += (int) p.blue * weight;
  return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned short)sum.red;
  current_pixel->green = (unsigned short)sum.green;
  current_pixel->blue = (unsigned short)sum.blue;
  return;
}

/* 
 * weighted_combo - Returns new pixel value at (i,j) 
 */
static pixel weighted_combo(int dim, int i, int j, pixel *src) 
{
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;
  double weights[3][3] = { { 0.50, 0.03125, 0.00 },
                           { 0.03125, 0.25, 0.03125 },
                           { 0.00, 0.03125, 0.125 } };

  initialize_pixel_sum(&sum);
  for(ii=0; ii < 3; ii++)
    for(jj=0; jj < 3; jj++) 
      if ((i + ii < dim) && (j + jj < dim))
        accumulate_weighted_sum(&sum,
                                src[RIDX(i+ii,j+jj,dim)],
                                weights[ii][jj]);
    
  assign_sum_to_pixel(&current_pixel, sum);
 
  return current_pixel;
}

/******************************************************
 * Your different versions of the motion kernel go here
 ******************************************************/

/*
 * naive_motion - The naive baseline version of motion 
 */
char naive_motion_descr[] = "naive_motion: Naive baseline implementation";
void naive_motion(int dim, pixel *src, pixel *dst) 
{
  int i, j;
    
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = weighted_combo(dim, i, j, src);
}




/**********************************
 * MINE!!!! BELOW!!!!!
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(int dim, pixel *src, pixel *dst) 
{
  int i, j;

//HELPER FUNC DECS
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;

 
  for (i = 0; i < dim; i++){
    for (j = 0; j < dim; j++){
      //helper..
       //initialize_pixel_sum(&sum);
       	sum.red = 0;
	sum.green = 0;
	sum.blue = 0;

      
	ii = 0;
     	jj = 0;

	//double weight;
	pixel p;
 	p = src[RIDX(i+ii,j+jj,dim)];   
           if ((i + ii < dim) && (j + jj < dim)){
              	//p = src[RIDX(i+ii,j+jj,dim)];                
		sum.red += (int) p.red >>1;
  		sum.green += (int) p.green >>1;
  		sum.blue += (int) p.blue >>1;
           }
//0, 1
     	jj++;
 	p = src[RIDX(i+ii,j+jj,dim)];   

           if ((i + ii < dim) && (j + jj < dim)){
              	//p = src[RIDX(i+ii,j+jj,dim)];                
		sum.red += (int) p.red >> 5;
  		sum.green += (int) p.green >> 5;
  		sum.blue += (int) p.blue >> 5;
           }
//0,2

	ii = 1;
     	jj = 0;
 	p = src[RIDX(i+ii,j+jj,dim)];   
           if ((i + ii < dim) && (j + jj < dim)){
              //	p = src[RIDX(i+ii,j+jj,dim)];                
		sum.red += (int) p.red >> 5;
  		sum.green += (int) p.green >> 5;
  		sum.blue += (int) p.blue >> 5;

           }
     	jj++;
//1,1
	p = src[RIDX(i+ii,j+jj,dim)];   
           if ((i + ii < dim) && (j + jj < dim)){
                               
		sum.red += (int) p.red >>2;
  		sum.green += (int) p.green >> 2;
  		sum.blue += (int) p.blue >> 2;

           }
     	jj++;
//1,2
	p = src[RIDX(i+ii,j+jj,dim)];   

           if ((i + ii < dim) && (j + jj < dim)){

              //	p = src[RIDX(i+ii,j+jj,dim)];                
		sum.red += (int) p.red >> 5;
  		sum.green += (int) p.green >>5;
  		sum.blue += (int) p.blue >>5;

           }
	ii = 2;
     	jj = 1;

//2,1
	p = src[RIDX(i+ii,j+jj,dim)];   
           if ((i + ii < dim) && (j + jj < dim)){        
		sum.red += (int) p.red >> 5;
  		sum.green += (int) p.green >> 5;
  		sum.blue += (int) p.blue >> 5;

           }
     	jj++;
//2,2
	p = src[RIDX(i+ii,j+jj,dim)];   
           if ((i + ii < dim) && (j + jj < dim)){
               
                          
		sum.red += (int) p.red >> 3;
  		sum.green += (int) p.green >> 3;
  		sum.blue += (int) p.blue >>3;
           }

		current_pixel.red = (unsigned short)sum.red;
 		current_pixel.green = (unsigned short)sum.green;
    		current_pixel.blue = (unsigned short)sum.blue;


           dst[RIDX(i, j, dim)] = current_pixel;


       }
    }
  
}

/********************************************************************* 
 * register_motion_functions - Register all of your different versions
 *     of the motion kernel with the driver by calling the
 *     add_motion_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_motion_functions() {
  add_motion_function(&motion, motion_descr);
  add_motion_function(&naive_motion, naive_motion_descr);
}

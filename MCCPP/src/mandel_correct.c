/*
 *
 * The answer key to mandel_wrong.c. No peeking!
 *
 * Author: Matt Cufari
 * Version 1.1.0
 * Date Created Jan 4 2021
 * Date Last Modified Jan 4 2021
 */



#include <omp.h>
#include <stdio.h>

#define NPOINTS 1000
#define MXITR 10000

struct d_complex{
	double r; double i;
};

void testpoint(struct d_complex);

struct d_complex c;
int numoutside = 0;

int main(){
	int i,j;
	double area, error, eps = 1.0e-7;
        //////////////////////////////////////
	//		Answer
	//////////////////////////////////////
#pragma omp parallel for default(shared) private(c, j) firstprivate(eps)
	for(i = 0; i < NPOINTS; i++){
		for(j = 0; j<NPOINTS; j++){
			c.r = -2.0 + 2.5*(double)(i)/((double)(NPOINTS)+eps);
			c.i = 1.125 * (double)(j)/((double)(NPOINTS)+eps);
			testpoint(c);
		}
	}
	printf("NUMOUTSIDE: %d\n", numoutside);
	area = 2.0*2.5*1.125 * (double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
	error = area/(double)NPOINTS;
	printf("Area is: %f\n", area);
	printf("error is: %f\n", error);
}

void testpoint(struct d_complex c){
	struct d_complex z;
	int iter;
	double temp;
	z = c;
	for(iter = 0; iter<MXITR; iter++){
		temp = (z.r*z.r)-(z.i*z.i)+c.r;
		z.i = z.r*z.i*2+c.i;
		z.r = temp;
		if((z.r*z.r + z.i*z.i) > 4.0){
		   //////////////////////////////
		   //		Answer
		   //////////////////////////////
		   #pragma omp atomic
			numoutside++;
			break;
		}
	}
}

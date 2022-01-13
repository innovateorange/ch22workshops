/*
 * Parallel pi calculator using array padding to avoid memory collisions
 *
 * Author: Matt Cufari
 * Version 1.0.0
 * Date Created: Dec 18 2020
 * Date last modified: Jan 4 2021
 *
 */

/*
 * This program is extra content if there is time to cover
 */

#include "omp.h"
#include <stdio.h>

#define NUM_THREADS 6
#define PAD 8
static long num_steps = 1000000;
double step;

int main(){
	int i;
	int nthreads;
	
	double pi = 0;
	double sum[NUM_THREADS][PAD];

	step=1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
	{
		int i;
		int id;
		int nthrds;
		double x;
		id = omp_get_thread_num();
		printf("Hello from %d\n", id);
		nthrds = omp_get_num_threads();
		if(id == 0) {
			nthreads = nthrds;
		}
		for(i=id, sum[id][0]=0.0; i<num_steps; i=i+nthrds){
			x = (i+0.5)*step;
			sum[id][0] += 4.0 / (1.0+x*x);
		}
	}
	for(i = 0, pi=0.0; i < nthreads; i++){
		pi += sum[i][0]*step;
	}
	printf("The value of pi is: %f\n", pi);
	return 0;
}



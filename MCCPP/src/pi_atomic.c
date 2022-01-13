/*
 * A parallel pi program using atomic operations
 *
 * Author: Matt Cufari
 * Version: 1.0.0
 * Date Created Dec 18 2020
 * Date Last Modified Jan 4 2021
 */




#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

#define NUM_THREADS 2
void main(){
	double pi;
	int nthreads;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
	{
		int i, id, nthrds;
		double x, sum;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if(id == 0) nthreads = nthrds;
		for(i = id, sum=0.0; i < num_steps; i=i+nthreads){
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}
		sum = sum*step;
	#pragma atomic
		pi += sum;
		
	}
	printf("The value of pi is: %f\n", pi);
}


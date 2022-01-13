/*
 * A parallel pi program using OpenMP critical operations
 *
 * Author: Matt Cufari
 * Version 1.1.0
 * Date Created: Dec 18 2020
 * Date Last Modified: Jan 4 2021
 *
 */






#include <stdio.h>
#include <omp.h>

static long  num_steps = 1000000;
double step; //dx

#define NUM_THREADS 4 //Maximum number of requested threads

void main(){
	
	double pi = 0.0;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS); //Same as before

#pragma omp parallel //parallel block
	{
		int i, id, nthrds; 
		double x, sum; //Sum is now thread local
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		for(i = id, sum=0.0; i<num_steps; i=i+nthrds){
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}

#pragma omp critical
	pi += sum*step; //Mutually exclusive update
	
	}

	printf("The value of pi is: %f\n", pi);
}

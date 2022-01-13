/*
 *Parallelized version of pi_serial. Compare performance with time ./pi_parallel 
 * and time ./pi_serial
 *
 * Author: Matt Cufari
 * Version 1.1.0
 * Date Created: Dec 18 2020
 * Date Last Modified: Jan 4 2021
 *
 */



#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 2 //Thread count macro

static long num_steps = 1000000; //number of rectangles
double step; //dx

int main(){
	int i; //index of rectangle
	int nthreads; //number of threads
	
	double pi = 0; //value of pi
	double sum[NUM_THREADS]; //Sum is now an array and the riemann sum is SUM over sum[]

	step=1.0/(double) num_steps; //dx
	omp_set_num_threads(NUM_THREADS); //Set number of threads

#pragma omp parallel //Parallel block
	{
		int i; //index of rectangel (thread local)
		int id; //id of thread (thread local)
		int nthrds; //number of threads (thread local)
		double x; //Position on x-axis (thread local)
		id = omp_get_thread_num(); //Get id
		
		nthrds = omp_get_num_threads(); //Get num_threads necessary for complex reason
		if(id == 0) {
			nthreads = nthrds; //Set the global variable. See loop over sum
		}
		for(i=id, sum[id]=0.0; i<num_steps; i=i+nthrds){ //i += nthrds !!!
			x = (i+0.5)*step; //midpoint of rectangle
			sum[id] += 4.0 / (1.0+x*x); //Same as before
		}
	} //End parallel block
	for(i = 0, pi=0.0; i < nthreads; i++){
		pi += sum[i]*step; //SUM over sum[] (* dx)
	}
	printf("The value of pi is: %f\n", pi);
	return 0;
}



/*
*  A program to compute the numerical value of pi in parallel
*
*  Author: Matthew Cufari (with notes from Tim Mattson @ Intel)
*  Version: 1.0.0
*  Date Created: Dec 18 2020
*
*/



#include <omp.h>
#include <stdio.h>


static long num_steps = 1000000;
double step;
int main(){

	int i;
	double pi = 0;
	double sum = 0;

	step = 1.0/(double) num_steps;
#pragma omp parallel
	{
		double x;

		#pragma omp for reduction(+:sum)
		for(i = 0; i < num_steps; i++){
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}

	}
	pi = step * sum;
	printf("The Value of Pi is: %f\n", pi);
	return 0;

}


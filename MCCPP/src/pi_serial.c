/*
*  A program to compute the numerical value of pi in serial
*
*  Author: Matthew Cufari (with notes from Tim Mattson @ Intel)
*  Version: 1.1.0
*  Date Created: Dec 18 2020
*  Date last modified: Jan 4 2021
*/



#include <omp.h>
#include <stdio.h>


static long num_steps = 1000000; //1 million partitions
double step; //dx
int main(){

	int i; //index
	double x = 0; //x-axis value
	double pi = 0; //pi-final value
	double sum = 0; //running riemann sum

	step = 1.0/(double) num_steps; //Step size (integrating from 0-1)

	for(i = 0; i < num_steps; i++){
		x = (i+0.5)*step; //midpoint riemann sum
		sum = sum + 4.0/(1.0+x*x); //riemann summation
	}
	pi = step*sum; //multiply by dx
	
	printf("The Value of Pi is: %f\n", pi); 
	return 0;

}


/*
 * A simple Hello World From Thread 0 Program
 *
 * Author: Matt Cufari
 * Version: 1.0.0
 * Date Created: Jan 4 2021
 * Date Last Modified: Jan 12 2022
 *
 *
 */



#include <stdio.h>
#include <omp.h>

int main(){
#pragma omp parallel //Create a parallel block 
{
	int ID = omp_get_thread_num(); //Set the ID
	

	printf("Hello (%d) ", ID); //Hello (ID)
	printf("world (%d) \n", ID); //World (ID)
	
	/*
	 * The output of this program will look nonsensical because threads do not execute
	 * one-after another
	 *
	 * How do we modify this program so that the threads aren't racing against one another?
	 */

	// Mutual Exclusion!	

}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
	 
#define NALLOCATIONS 334
#define MINBYTES 3000000
#define MAXBYTES 3000000

int main(){
	clock_t begin = clock();
	int* allocs[NALLOCATIONS];
	for(int i=0; i<NALLOCATIONS; i++){
		int random_size = (rand() % (MAXBYTES - MINBYTES + 1)) + MINBYTES;
		// memory allocation
		allocs[i] = (int*) malloc(random_size);

		// memory usage
		for(int k=0; k<750000; k++){
			allocs[i][k]=10;
		}
	}
	// memory free
	for(int j=0; j<NALLOCATIONS; j++){
		free(allocs[j]);
	}
	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %f \n", time_spent);
}

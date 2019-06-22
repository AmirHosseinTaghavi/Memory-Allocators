#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
	 
#define NTHREADS 4
#define NALLOCATIONS 50000
#define MINBYTES 10000
#define MAXBYTES 10000

void *thread_function(void *);

int main(){
	clock_t begin = clock();
	pthread_t thread_id[NTHREADS];
	int i, j;
	 
	for(i=0; i < NTHREADS; i++){
		srand(time(0));
		pthread_create( &thread_id[i], NULL, thread_function, NULL );
	}
	 
	for(j=0; j < NTHREADS; j++){
		pthread_join( thread_id[j], NULL);
	}

	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %f \n", time_spent);

	return 0;
}
	 
void *thread_function(void *ptr){
	//printf("Thread number %ld\n", pthread_self());
	int* allocs[NALLOCATIONS];
	for(int i=0; i<NALLOCATIONS; i++){
		int random_size = (rand() % (MAXBYTES - MINBYTES + 1)) + MINBYTES;
		// memory allocation
		allocs[i] = (int*) malloc(random_size);
		// memory usage
		for(int k=0; k<2500; k++){
			allocs[i][k]=10;
		}
	}
	// memory free
	for(int j=0; j<NALLOCATIONS; j++){
		free(allocs[j]);
	}
}

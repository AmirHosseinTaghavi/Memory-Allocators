#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
	 
#define NTHREADS 4
#define NALLOCATIONS 50
#define MINBYTES 10000
#define MAXBYTES 100000
void *thread_function(void *);

int main(){
	pthread_t thread_id[NTHREADS];
	int i, j;
	 
	for(i=0; i < NTHREADS; i++){
		srand(time(0));
		pthread_create( &thread_id[i], NULL, thread_function, NULL );
	}
	 
	for(j=0; j < NTHREADS; j++){
		pthread_join( thread_id[j], NULL);
	}

	return 0;
}
	 
void *thread_function(void *ptr){
	//printf("Thread number %ld\n", pthread_self());
	int* allocs[NALLOCATIONS];	
	for(int i=0; i<NALLOCATIONS; i++){
		int random_size = (rand() % (MAXBYTES - MINBYTES + 1)) + MINBYTES;
		//printf("Size = %d\n", random_size);
		allocs[i] = (int*) malloc(random_size);
	}
	for(int j=0; j<NALLOCATIONS; j++){
		free(allocs[j]);
	}
}


	




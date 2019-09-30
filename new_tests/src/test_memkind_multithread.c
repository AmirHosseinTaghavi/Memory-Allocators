#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <memkind.h>

void *thread_function(void *);

struct args {
    int thread_allocs_count;
	int alloc_size;
};

int main(int argc, char *argv[]){
	int thread_count= atoi(argv[1]);  
    int thread_allocs_count = atoi(argv[2]); 
    int alloc_size = atoi(argv[3]); 
	pthread_t thread_id[thread_count];
	int i, j;

	struct args *thread_args = (struct args *)malloc(sizeof(struct args));
    thread_args->thread_allocs_count = thread_allocs_count;
	thread_args->alloc_size = alloc_size;
	 
	for(i=0; i < thread_count; i++){
		srand(time(0));
		pthread_create( &thread_id[i], NULL, thread_function, (void *)thread_args );
	}
	 
	for(j=0; j < thread_count; j++){
		pthread_join( thread_id[j], NULL);
	}

	return 0;
}
	 
void *thread_function(void *args){
	//printf("Thread number %ld\n", pthread_self());
	int thread_allocs_count = ((struct args*)args)->thread_allocs_count;
	int alloc_size = ((struct args*)args)->alloc_size;
	FILE *fptr;
	fptr = fopen("src/result.txt", "a");
	int* allocs[thread_allocs_count];
	
	clock_t begin = clock();
	for(int i=0; i<thread_allocs_count; i++){
		// memory allocation
		allocs[i] = (int*) memkind_malloc(MEMKIND_HUGETLB, alloc_size);
	}
	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	fprintf(fptr,"%f\n", time_spent);
   	fclose(fptr);

	for(int i=0; i<thread_allocs_count; i++){
		// memory usage
		for(int k=0; k<alloc_size/4; k++){
			allocs[i][k]=10;
		}
	}
	
	// memory free
	for(int j=0; j<thread_allocs_count; j++){
		memkind_free(MEMKIND_HUGETLB, allocs[j]);
	}
}

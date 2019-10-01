#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <memkind.h>

void *thread_function(void *);

struct args {
    int thread_allocs_count;
};

int main(int argc, char *argv[]){
	int thread_count= atoi(argv[1]);  
    int thread_allocs_count = atoi(argv[2]); 
	pthread_t thread_id[thread_count];
	int i, j;

	struct args *thread_args = (struct args *)malloc(sizeof(struct args));
    thread_args->thread_allocs_count = thread_allocs_count;
	 
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
	FILE *fptr;
	fptr = fopen("src/result.txt", "a");
	int* allocs[thread_allocs_count];

	FILE *input_file;
    input_file = fopen("src/input_sizes.txt", "r");
    int size_array[thread_allocs_count];
    int i;
    for (i = 0; i < thread_allocs_count; i++){
        fscanf(input_file, "%d,", &size_array[i] );
    }
    fclose(input_file);
	
	struct timeval start, end;
	gettimeofday(&start, NULL); 
	for(int i=0; i<thread_allocs_count; i++){
		// memory allocation
		allocs[i] = (int*) memkind_malloc(MEMKIND_HUGETLB, size_array[i]);
	}
	gettimeofday(&end, NULL);
	double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6; 
	fprintf(fptr,"%f\n", time_taken);
   	fclose(fptr);

	for(int i=0; i<thread_allocs_count; i++){
		// memory usage
		for(int k=0; k<size_array[i]/4; k++){
			allocs[i][k]=10;
		}
	}
	
	// memory free
	for(int j=0; j<thread_allocs_count; j++){
		memkind_free(MEMKIND_HUGETLB, allocs[j]);
	}
}

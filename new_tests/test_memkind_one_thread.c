#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <memkind.h>
	 
#define NALLOCATIONS 334
/// objbytes 3000 kb
// run with ./test_memkind_one 3000

int main(int argc, char* argv[]){
	// in kb
	int object_size = atoi(argv[1]);

	clock_t begin = clock();
	int* allocs[NALLOCATIONS];
	for(int i=0; i<NALLOCATIONS; i++){
		// memory allocation
		allocs[i] = (int*) memkind_malloc(MEMKIND_HUGETLB, object_size*1000);
		// memory usage
		for(int k=0; k<750000; k++){
			allocs[i][k]=10;
		}
	}
	// memory free
	for(int j=0; j<NALLOCATIONS; j++){
		memkind_free(MEMKIND_HUGETLB, allocs[j]);
	}
	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %f \n", time_spent);
}

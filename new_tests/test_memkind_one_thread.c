#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <memkind.h>
	 
// objbytes 3000 kb
// number of allocations 334
// ./test_memkind_one allocations_number object_size
// run with ./test_memkind_one 334 3000

int main(int argc, char* argv[]){
	// in kb
	int alloc_num = atoi(argv[1]);
	int object_size = atoi(argv[2]);

	FILE* fp = fopen("/proc/sys/vm/nr_hugepages", "w");
	int hugepage_nums = ((alloc_num * object_size) / 1000) / 2 + 1;
	fprintf(fp, "%d", hugepage_nums);

	clock_t begin = clock();
	int* allocs[alloc_num];
	for(int i=0; i<alloc_num; i++){
		// memory allocation
		allocs[i] = (int*) memkind_malloc(MEMKIND_HUGETLB, object_size*1000);
		// memory usage
		int nums_in_object = (object_size*1000) / 4;
		for(int k=0; k<nums_in_object; k++){
			allocs[i][k]=10;
		}
	}
	// memory free
	for(int j=0; j<alloc_num; j++){
		memkind_free(MEMKIND_HUGETLB, allocs[j]);
	}
	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %f \n", time_spent);
}

#include <memkind.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

	int *ptr;
	int num = 25000000;

	clock_t begin = clock();
	ptr = (int*) memkind_malloc(MEMKIND_HUGETLB, num * sizeof(int));
	clock_t end = clock();
	double time_spent_first = (double) (end - begin) / CLOCKS_PER_SEC;

	printf("time spent first= %f \n", time_spent_first);

	clock_t begin1 = clock();
	for(int i=0; i< num; i++){
		ptr[i] = i%10000;
	}
	clock_t end1 = clock();
	double time_spent_allocation = (double) (end1 - begin1) / CLOCKS_PER_SEC;

	printf("time spent while allocation= %f \n", time_spent_allocation);

	sleep(2);

	memkind_free(MEMKIND_HUGETLB, ptr);
	return 0;
}

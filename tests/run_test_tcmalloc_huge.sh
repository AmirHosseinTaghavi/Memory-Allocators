#!/bin/bash

# note: must run with root
# arguments: thread_count, thread_allocs_count, alloc_size, exeutions_count, hugepages_count, input_type
# input_types: 1-> fixed, 2-> random

export LD_PRELOAD=/usr/local/lib/libtcmalloc_minimal.so.4
echo $5 > /proc/sys/vm/nr_hugepages
mount -t hugetlbfs none /mnt/huge/
export TCMALLOC_MEMFS_MALLOC_PATH=/mnt/huge/
gcc -o test_tcmalloc_huge_multithread src/test_multithread.c -lpthread

truncate -s 0 src/result.txt

if [ "$6" -eq "1" ] 
then 
	python3 src/generate_input.py $6 $3 $2 0 
fi

for (( c=1; c<=$4; c++ ))
do
	./test_tcmalloc_huge_multithread $1 $2
done

rm test_tcmalloc_huge_multithread

python3 src/calc_time.py $1

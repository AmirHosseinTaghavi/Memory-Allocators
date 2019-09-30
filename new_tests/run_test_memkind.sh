#!/bin/bash

# note: must run with root
# arguments: thread_count, thread_allocs_count, alloc_size, exeutions_count, hugepages_count

echo $5 > /proc/sys/vm/nr_hugepages
gcc -o test_memkind_multithread src/test_memkind_multithread.c -lmemkind -lpthread

truncate -s 0 src/result.txt

for (( c=1; c<=$4; c++ ))
do
	./test_memkind_multithread $1 $2 $3
done

rm test_memkind_multithread

python3 src/calc_time.py $1

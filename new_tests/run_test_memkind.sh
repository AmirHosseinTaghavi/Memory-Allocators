#!/bin/bash

# note: must run with root
# arguments: thread_count, thread_allocs_count, alloc_size, exeutions_count, hugepages_count, input_type
# input_types: 1-> uniform

echo $5 > /proc/sys/vm/nr_hugepages
gcc -o test_memkind_multithread src/test_memkind_multithread.c -lmemkind -lpthread

truncate -s 0 src/result.txt
truncate -s 0 src/input_sizes.txt

python3 src/generate_input.py $6 $3 $2

for (( c=1; c<=$4; c++ ))
do
	./test_memkind_multithread $1 $2
done

rm test_memkind_multithread

python3 src/calc_time.py $1

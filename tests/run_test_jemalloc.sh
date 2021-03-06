#!/bin/bash

# arguments: thread_count, thread_allocs_count, alloc_size, exeutions_count, input_type
# input_types: 1-> fixed, 2-> random

export LD_PRELOAD=/usr/local/lib/libjemalloc.so
gcc -o test_jemalloc_multithread src/test_multithread.c -lpthread

truncate -s 0 src/result.txt

if [ "$5" -eq "1" ] 
then 
	python3 src/generate_input.py $5 $3 $2 0 
fi

for (( c=1; c<=$4; c++ ))
do
	./test_jemalloc_multithread $1 $2
done

rm test_jemalloc_multithread

python3 src/calc_time.py $1

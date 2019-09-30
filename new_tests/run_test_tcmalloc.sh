#!/bin/bash

# arguments: thread_count, thread_allocs_count, alloc_size, exeutions_count

export LD_PRELOAD=/usr/local/lib/libtcmalloc_minimal.so.4
gcc -o test_tcmalloc_multithread src/test_multithread.c -lpthread

truncate -s 0 src/result.txt

for (( c=1; c<=$4; c++ ))
do
	./test_tcmalloc_multithread $1 $2 $3
done

rm test_tcmalloc_multithread

python3 src/calc_time.py $1
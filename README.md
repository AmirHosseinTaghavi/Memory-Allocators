# Memory-Allocators

## jemalloc:

export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so

gcc test_jemalloc.c -o test_jemalloc

## memkind:

sudo echo 55 > /proc/sys/vm/nr_hugepages

gcc -o test_memkind test_memkind.c -lmemkind

## tcmalloc:

export LD_PRELOAD=/usr/lib/libtcmalloc_minimal.so.4

gcc -o test_tcmalloc test_tcmalloc.c

## tcmalloc+hugepage:

sudo su

export LD_PRELOAD=/usr/lib/libtcmalloc_minimal.so.4

echo 55 > /proc/sys/vm/nr_hugepages

mount -t hugetlbfs none /mnt/huge/

export TCMALLOC_MEMFS_MALLOC_PATH=/mnt/huge/

gcc -o test_tcmalloc test_tcmalloc.c

## ptmalloc:

gcc -o test_ptmalloc test_ptmalloc.c

it's default.

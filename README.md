# Memory-Allocators

## jemalloc:

export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so

make

## memkind:

sudo echo 55 > /proc/sys/vm/nr_hugepages

make

## tcmalloc:

export LD_PRELOAD=/usr/lib/libtcmalloc_minimal.so.4

make

## tcmalloc+hugepage:

sudo su

export LD_PRELOAD=/usr/lib/libtcmalloc_minimal.so.4

echo 55 > /proc/sys/vm/nr_hugepages

mount -t hugetlbfs none /mnt/huge/

export TCMALLOC_MEMFS_MALLOC_PATH=/mnt/huge/

make

## ptmalloc:

make

it's default.

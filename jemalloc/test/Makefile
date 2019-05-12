all:
	gcc test_jemalloc.c -o test_jemalloc -I`jemalloc-config --includedir` -L`jemalloc-config --libdir` -Wl,-rpath,`jemalloc-config --libdir` -ljemalloc `jemalloc-config --libs`

clean:
	rm -rf test_jemalloc

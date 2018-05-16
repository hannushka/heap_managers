bud:
	echo 'running buddy'
	cp buddy/malloc.c ../gawk-3.1.8
	make run

bud2:
	echo 'running buddy2'
	cp buddy2/malloc.h ../gawk-3.1.8
	cp buddy2/malloc.c ../gawk-3.1.8
	make run

linked:
	echo 'running linked list'
	cp linked_list/malloc.c ../gawk-3.1.8
	make run

run:
	cd ../gawk-3.1.8 && make check

clean:
	cd ./buddy && rm -f *.o && rm -f *.out
	cd ./buddy2 && rm -f *.o && rm -f *.out

test-bud:
	cd ./buddy2 && gcc test.c -o test.o && ./test.o

test-prev:
	cd ./buddy && gcc test.c -o test.o && ./test.o

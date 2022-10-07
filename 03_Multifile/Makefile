GENERATES = prog prog-a prog-so
TRASH = *.o *.a *.so *.txt

CC = cc

all: prog prog-a prog-so

prog:	const.o fun.o prog.o
	${CC} const.o fun.o prog.o -o prog

prog-a:	prog.o build-lib-a
	${CC} liboutput_static.a prog.o -o prog-a

prog-so: prog.o build-lib-so
	${CC} liboutput.so prog.o -o prog-so

%.o: %.c
	${CC} $< -c -o $@

build-lib-a:	fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o

build-lib-so:	fun.o const.o
	${CC} -shared fun.o const.o -o liboutput.so

test-%: %
	./$< > out-$<-0.txt
	./$< first > out-$<-1.txt
	./$< first second third > out-$<-3.txt

cmp-tests:
	cmp out-prog-0.txt out-prog-a-0.txt
	cmp out-prog-a-0.txt out-prog-so-0.txt
	cmp out-prog-so-0.txt out-prog-0.txt
	cmp out-prog-1.txt out-prog-a-1.txt
	cmp out-prog-a-1.txt out-prog-so-1.txt
	cmp out-prog-so-1.txt out-prog-1.txt
	cmp out-prog-3.txt out-prog-a-3.txt
	cmp out-prog-a-3.txt out-prog-so-3.txt
	cmp out-prog-so-3.txt out-prog-3.txt


test: test-prog test-prog-a test-prog-so cmp-tests
	@ echo tests passed

clean:
	rm -rf ${GENERATES} ${TRASH}

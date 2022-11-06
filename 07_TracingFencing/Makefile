CC = gcc
CFLAGS = -O3 -Wall
SO_FLAGS = -shared -fPIC
GENERATES = move

TRASH = *.out *.so *.txt *.expected

EXTRACT_CODE = 2>&1 >/dev/null | grep -o '[0-9]*'

move: move.c

remove.so: remove.c
	cc $(SO_FLAGS) $^ -o  $@ -ldl

preload:
	LD_PRELOAD=./remove.so ./move first.txt second.txt

populate-file:
	echo "Hello world\nIt's me" > first.txt

test-ok: populate-file
	./move first.txt second.txt $(EXTRACT_CODE) > test-ok.out
	echo 0 > test-ok.expected
	cmp test-ok.out test-ok.expected

test-open-file: populate-file
	strace -e open ./move first.txt second.txt $(EXTRACT_CODE) > test-open-file.out
	echo 1 > test-open-file.expected
	cmp test-open-file.out test-open-file.expected

test-writing-to-file: populate-file
	strace -e write ./move first.txt second.txt $(EXTRACT_CODE) > test-writing-to-file.out
	echo 2 > test-writing-to-file.expected
	cmp test-writing-to-file.out test-writing-to-file.expected

test-closing-file: populate-file
	strace -e close ./move first.txt second.txt $(EXTRACT_CODE) > test-closing-file.out
	echo 3 > test-closing-file.expected
	cmp test-closing-file.out test-closing-file.expected

test-removing-file: populate-file
	strace -e unlink ./move first.txt second.txt $(EXTRACT_CODE) > test-removing-file.out
	echo 4 > test-removing-file.expected
	cmp test-removing-file.out test-removing-file.expected

test: test-ok test-open-file test-writing-to-file test-closing-file test-removing-file
	@ echo tests passed

clean:
	rm -rf ${GENERATES} ${TRASH}

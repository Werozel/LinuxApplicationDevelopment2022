GENERATES = range.o
TRASH = *.o *.log *.dSYM

CC = cc

build:
	${CC} -O0 -g range.c -o ${GENERATES}

test-first:
	gdb --batch --quiet -x first.gdb --args ./range.o 1 12
	grep -o "{.*}" first.log > first_tmp.log
	cmp first_tmp.log first_correct

test-second:
	gdb --batch --quiet -x second.gdb --args ./range -100 100 3
	grep -o "{.*} second.log > second_tmp.log
	cmp second_tmp.log second_correct

test: test-first test-second
	@ echo tests passed

clean:
	rm -rf ${TRASH} ${GENERATES}

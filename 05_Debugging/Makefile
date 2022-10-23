TRASH = *.o *.log *.dSYM

build:
	gcc -O0 -g range.c -o range.o

test: range
	gdb --batch --quiet -x first.gdb --args ./range.o 1 12
	grep -Po "(?<=@@@\{).*(?=\})" first.log | sed 's/,//g' > first_tmp.log
	cmp first_tmp.log first_correct

	gdb --batch --quiet -x second.gdb --args ./range -100 100 3
	grep -Po "(?<=@@@\{).*(?=\})" second.log | sed 's/,//g' > second_tmp.log
	cmp second_tmp.log second_correct

clean:
	rm -rf $(TRASH)

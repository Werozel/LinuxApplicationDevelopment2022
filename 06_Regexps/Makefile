CC = cc
CFLAGS = -O3 -Wall
GENERATES = esub

TRASH = *.out

esub: esub.c

test-first:
	./esub "abc" "a" "9" > first_esub.out
	echo "abc" | sed -E "s/a/9/" > first_sed.out
	cmp first_esub.out first_sed.out

test-second:
	./esub "abc" "" "9" > second_esub.out
	echo "Error compiling regex: empty (sub)expression" > second_sed.out
	cmp second_esub.out second_sed.out

test-third:
	./esub "1a2b3c4" "[0-9]" "A" > third_esub.out
	echo "1a2b3c4" | sed -E "s/[0-9]/A/" > third_sed.out
	cmp third_esub.out third_sed.out

test: test-first test-second test-third
	@ echo tests passed

clean:
	rm -rf ${GENERATES} ${TRASH}

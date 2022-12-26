CFLAGS = -O0

bin_PROGRAMS = rhasher

rhasher_SOURCES = rhasher.c

TESTS = test-md5.sh test-sha1.sh

test-md5.sh:
	echo "test `echo 'MD5 "test' | ./rhasher` = `echo -n test | md5sum | sed 's/ .*//'`" > $@
	chmod +x $@

test-sha1.sh:
	echo "test `echo 'SHA1 "test' | ./rhasher` = `echo -n test | sha1sum | sed 's/ .*//'`" > $@
	chmod +x $@

clean:
	git clean -fd

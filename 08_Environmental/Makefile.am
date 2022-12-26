CFLAGS = -O0

bin_PROGRAMS = rhasher

rhasher_SOURCES = rhasher.c

test-md5:
    echo "MD5 \"test" | ./rhasher > test-md5.out
    echo "MD5 \"test" | md5sum > test-md5-tmp.ref
    sed 's/ .*//' test-md5-tmp.ref > test-md5.ref
    cmp test-md5.out test-md5.ref

test-sha1:
    echo "SHA1 \"test" | ./rhasher > test-sha1.out
    echo "SHA1 \"test" | sha1sum > test-sha1-tmp.ref
    sed 's/ .*//' test-sha1-tmp.ref > test-sha1.ref
    cmp test-sha1.out test-sha1.ref

clean:
	git clean -fd

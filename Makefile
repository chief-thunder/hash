# Compiles the hash source code to an executable.

main: hashtest.c
	BINDIR=bin
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	echo "Compiling the code... ⏳"
	gcc hashtest.c -o bin/hashtest

clean:
	rm -f bin/hashtest
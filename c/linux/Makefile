# Compiles the hash source code to an executable.

main: hashtest-linux.c
	BINDIR=bin
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	echo "Compiling the code... ⏳"
	gcc hashtest-linux.c -o bin/hashtest-linux

clean:
	rm -f bin/hashtest-linux
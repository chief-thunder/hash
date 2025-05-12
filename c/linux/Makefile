# Compiles the hash source code to an executable.

# Set binary directory.
BINDIR=bin

main: hashtest-linux.c
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	echo "Compiling the code... ⏳"
	gcc hashtest-linux.c -o bin/hashtest-linux

clean:
	rm -f bin/hashtest-linux
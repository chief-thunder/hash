# Compiles the hash source code to an executable.

main: hashtest-macos.c
	BINDIR=bin
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	echo "Compiling the code... ⏳"
	print: $(wildcard *.c)
	gcc hashtest-macos.c -o bin/hashtest-macos

clean:
	rm -f bin/hashtest-macos
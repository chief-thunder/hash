# Compiles the hash source code to an executable.

# Set binary directory.
BINDIR=bin

main: hashtest-macos.c
	export LDFLAGS="-L/opt/homebrew/opt/openssl/lib"
	export CPPFLAGS="/opt/homebrew/opt/openssl/include/openssl/"
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	echo "Compiling the code... ⏳"
	gcc hashtest-macos.c -o bin/hashtest-macos -I/opt/homebrew/opt/openssl/include/openssl/ -L/opt/homebrew/opt/openssl/lib -lcrypto

clean:
	rm -f bin/hashtest-macos
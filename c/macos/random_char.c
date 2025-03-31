#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <string.h>

int main(void) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    const size_t charset_size = strlen(charset);
    unsigned char random_byte;
    
    // Get a random byte
    if (getentropy(&random_byte, sizeof(random_byte)) != 0) {
        perror("getentropy");
        return EXIT_FAILURE;
    }

    // Map the random byte to an index in the charset
    char random_char = charset[random_byte % charset_size];
    
    // Print the random character
    printf("Random character: %c\n", random_char);

    return EXIT_SUCCESS;
}
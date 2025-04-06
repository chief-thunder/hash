/*
    Hashing and salting passwords in C on macOS Sequoia.
    Written by ct 30/06/2024, with the help of ChatGPT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

// Define the charset
char charset[] = "abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"1234567890"
"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Function to get a random character from the charset
char get_random_char(const char *charset, size_t charset_length) {
    unsigned char random_byte;

    // Use getentropy to generate a random byte
    if (getentropy(&random_byte, sizeof(random_byte)) != 0) {
        perror("getentropy failed");
        exit(EXIT_FAILURE);
    }

    // Use the random byte to select a character from the charset
    return charset[random_byte % charset_length];
}

char getsalt(char mystr[]) {

    size_t charset_length = sizeof(charset) - 1; // Exclude the null terminator
    unsigned int x;

    for(x = 0; x < 10; x++) {
        mystr[x] = get_random_char(charset, charset_length);
    }

    return mystr[10];
}

int main(void) {

    size_t charset_length = sizeof(charset) - 1; // Exclude the null terminator

    // Get a random character
    char random_char = get_random_char(charset, charset_length);

    // Print the random character
    printf("Random character: %c\n", random_char);

    // Generate a random salt
    char salt[11]; // 10 characters + null terminator
    getsalt(salt);
    salt[10] = '\0'; // Null-terminate the string
    printf("Random salt: %s\n", salt);


    return EXIT_SUCCESS;
}
/*
    Hashing and salting passwords in C on macOS Sequoia.
    Written 30/06/2024 by ct, with some help from ChatGPT on the entropy and random character part.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include "/opt/homebrew/opt/openssl/include/openssl/md5.h"
#include "/opt/homebrew/opt/openssl/include/openssl/sha.h"

// Define Character set. All alphanumeric characters, numbers and special characters.
char charset[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "1234567890"
                 "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Function to get a random character from the charset.
char get_random_char(const char *charset, size_t charset_length) {
    unsigned char random_byte;
    if (getentropy(&random_byte, sizeof(random_byte)) != 0) {
        perror("getentropy failed");
        exit(EXIT_FAILURE);
    }
    return charset[random_byte % charset_length];
}

// Function to generate a random salt.
void getsalt(char mystr[]) {
    size_t charset_length = sizeof(charset) - 1;
    for (unsigned int x = 0; x < 10; x++) {
        mystr[x] = get_random_char(charset, charset_length);
    }
    mystr[10] = '\0';
}

// Function to hash the input string using MD5.
void hash_md5(const char *input, char *output) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)input, strlen(input), digest);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", digest[i]);
    }
}

// Function to hash the input string using SHA256.
void hash_sha256(const char *input, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", digest[i]);
    }
}

// Function to hash the input string using the specified hash algorithm.
char *hashit(char hstr[], char hname[]) {
    static char md5_hash[MD5_DIGEST_LENGTH * 2 + 1];
    static char sha256_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    if (strcmp(hname, "md5") == 0) {
        hash_md5(hstr, md5_hash);
        return md5_hash;
    } else if (strcmp(hname, "sha256") == 0) {
        hash_sha256(hstr, sha256_hash);
        return sha256_hash;
    } else {
        fprintf(stderr, "Invalid hash name: %s\n", hname);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    size_t charset_length = sizeof(charset) - 1;
    char random_char = get_random_char(charset, charset_length);

    //char password[] = "Thisisreallyg00d!";
    // Define a password variable to hold the password.
    char password[100];
    // Get the password from the user.
    printf("Enter password: ");
    scanf("%s", password);

    char salt[11];
    getsalt(salt);

    // Print the password and salt.
    printf("\nPassword: %s\n", password);
    printf("Salt: %s\n", salt);

    // Salt the password by concatenating the salt and password.
    char salted_password[sizeof(salt) + sizeof(password) - 1];

    // Print the salted and unsalted password.
    sprintf(salted_password, "%s%s", salt, password);
    printf("Salted password: %s\n", salted_password);
    printf("MD5 Hash (unsalted): %s\n", hashit(password, "md5"));
    printf("MD5 Hash (salted): %s\n", hashit(salted_password, "md5"));
    printf("SHA256 Hash (unsalted): %s\n", hashit(password, "sha256"));
    printf("SHA256 Hash (salted): %s\n", hashit(salted_password, "sha256"));

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t length) {
    const char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char salted_password[256];
    snprintf(salted_password, sizeof(salted_password), "%s%s", salt, password);
    SHA256((unsigned char *)salted_password, strlen(salted_password), hash);
}

void print_hash(unsigned char *hash) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    const char *password = "Thisisreallyg00d!";
    char salt[SALT_LENGTH + 1];
    unsigned char hash[HASH_LENGTH];

    generate_salt(salt, SALT_LENGTH);
    printf("Password: %s\n", password);
    printf("Salt: %s\n", salt);

    hash_password(password, salt, hash);
    printf("SHA256 Hash (salted): ");
    print_hash(hash);

    return 0;
}
/*
    Hashing and salting passwords in C.
    Written by ct 30/06/2024.
*/

#include <stdio.h>
#include <stdlib.h>
//#include <sys/random.h>
#include <Security/Security.h>

// Create alphanumerical string with punctuation.
char charset[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "1234567890"
                 "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Set password.
char password[] = "Thisisreallyg00d!";

char choice(const char *charset, size_t length) {
    uint8_t randomIndex;
    int status = SecRandomCopyBytes(kSecRandomDefault, sizeof(randomIndex), &randomIndex);
    if (status != errSecSuccess) {
        fprintf(stderr, "Error generating random byte\n");
        exit(EXIT_FAILURE);
    }
    return charset[randomIndex % length];
}


// Create salt function
char getsalt(char saltstr[], size_t salt_length, const char *charset, size_t charset_length) {
    for (size_t i = 0; i < salt_length; i++) {
        saltstr[i] = choice(charset, charset_length);
    }
    saltstr[salt_length] = '\0'; // Null-terminate the salt string

    // Return the value.
    //return saltstr;
}

// Create salt function.
//char getsalt(char saltstr[])
//{

//}


int main(void)
{
    char salt[11] = 0;
    //int errSecSuccess = 0;
    //getentropy(&salt, 1);
    getsalt(salt, 10, charset, sizeof(charset) - 1);

    printf("Result: %s\n", salt);
/*
    short int bytes[10];
    int status = SecRandomCopyBytes(charset, (sizeof bytes)/(sizeof bytes[0]), &bytes);
        
    if (status == errSecSuccess) { // Always test the status.
        for (int i = 0; i < (sizeof bytes)/(sizeof bytes[0]); i++) {
            printf("%d", bytes[i]);
        }
        // Prints something different every time you run.
    }

    printf("This is the random: %s", secretkey);
*/
    int bob = 0;
    printf("bob: %ld\n", sizeof(bob));
    printf("Contents of charset: %s", charset);
    printf("Contents of password: %s", password);
    
    return 0;
}

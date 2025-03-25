/*
    Hashing and salting passwords in C.
    Written by ct 30/06/2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

// Create alphanumerical string with punctuation.
char charset[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "1234567890"
                 "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Set password.
char password[] = "Thisisreallyg00d!";

// Create salt function.
/*
char getsalt(char saltstr[])
{

}
*/

int main(void)
{
    int salt = 0;
    int errSecSuccess = 0;
    getentropy(&salt, 1);
    printf("Result: %d", salt);

    short int bytes[10];
    int status = getentropy(bytes, sizeof(bytes));
    int test = getentropy(charset, 10);
        
    if (status == 0) { // Always test the status.
        for (int i = 0; i < (sizeof bytes)/(sizeof bytes[0]); i++) {
            printf("%d ", bytes[i]);
        }
        printf("\n");
        // Prints something different every time you run.
    } else {
        printf("Failed to generate random bytes\n");
    }

    printf("This is the random: %d\n", status);
    printf("This is test: %d\n", test);
    printf("Result: %d\n", salt);

    int bob = 0;
    printf("bob: %ld\n", sizeof(bob));
    printf("Contents of charset: %s\n", charset);
    printf("Contents of password: %s\n", password);
    
    return 0;
}

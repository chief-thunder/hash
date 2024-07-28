/*
    Hashing and salting passwords in C.
    Written by ct 30/06/2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

// Create alphanumerical string with punctuation.
char charset[96] = "abcdefghijklmnopqrstuvwxyz"
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

    // Get a cryptographically secure random number to use as seed later.
    unsigned int tmp;
    
    getrandom(&tmp, sizeof(tmp), GRND_NONBLOCK) == -1
        ? perror("getrandom")
        : "";
    printf("tmp: %d\n", tmp);

    // Seed the random number generator.
    srand(tmp);

    // Generate a number within the specified range.
    int number = rand() % 96 + 1;
    printf("number: %d\n", number);
    printf("From charset we picked: %c which is at position %d\n", charset[number], number);
    unsigned int x = 93;
    printf("Position %d is %c\n", x, charset[x]);

    // print the whole array one by one.
    int i;
    for (i = 0; i < 96; i++)
    {
        printf("Element %d is %c\n", charset[i], charset[i]);
    }

    printf("Size of charset: %ld\n", sizeof(charset)+1);
    printf("Contents of charset: %s\n", charset);
    printf("Contents of password: %s\n", password);
    
    return 0;
}

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

    unsigned int tmp;

    getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK) == -1
        ? perror("getrandom")
        : "";
    printf("%u\n", tmp);

    exit(EXIT_SUCCESS);

    printf("This is the random: %s", secretkey);

    printf("Contents of charset: %s", charset);
    printf("Contents of password: %s", password);
    
    return 0;
}

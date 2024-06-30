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
char password[] = "Thisisreallyg00d";

// Create salt function.
/*
char getsalt(char saltstr[])
{

}
*/

int main(void)
{
    int salt = 0;
    getentropy(&salt, 1);
    printf("Result: %d", salt);
    //printf("Contents of charset: %s", charset);
    //printf("Contents of password: %s", password);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define ERROR_MESSAGE "Encryption of %s failed.\n"
#define SUCCESS_MESSAGE "Encryption of %s succeeded.\n"

int main(int argc, char *argv[])
{
    FILE *source_file = fopen(argv[1], "r");
    FILE *destination_file = fopen(argv[2], "w");

    srand(atoi(argv[3]));

    int is_empty = 1;

    char character;
    while ((character = fgetc(source_file)) != EOF)
    {
        is_empty = 0;
        int random = rand();
        fputc(character ^ random, destination_file);
        // printf("%c", character ^ random ^ random); // Test
    }

    if (is_empty)
        printf(ERROR_MESSAGE, argv[1]);
    else
        printf(SUCCESS_MESSAGE, argv[1]);

    return 0;
}

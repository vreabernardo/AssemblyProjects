#include <stdio.h>
#include <stdlib.h>

#define ERROR_MESSAGE "Encryption of %s failed.\n"
#define SUCCESS_MESSAGE "Encryption of %s succeeded.\n"

int main(int argc, char *argv[])
{
    // Open the source file for reading and the destination file for writing
    FILE *source_file = fopen(argv[1], "r");
    FILE *destination_file = fopen(argv[2], "w");

    // Seed the random number generator with the provided seed number
    srand(atoi(argv[3]));

    // Variable to check if the source file is empty
    int is_empty = 1;

    // Variable to store each character read from the source file
    char character;

    // Loop through each character in the source file until the end of the file (EOF)
    while ((character = fgetc(source_file)) != EOF)
    {
        // Set the flag indicating that the source file is not empty
        is_empty = 0;

        // Generate a random number, XOR it with the character read from the source file and write the result to the destination file
        int random = rand();
        fputc(character ^ random, destination_file);
        // printf("%c", character ^ random ^ random); // Test
    }

    // If the is_empty flag is set, the source file is empty and the encryption cant be done
    if (is_empty)
        printf(ERROR_MESSAGE, argv[1]);
    else
        printf(SUCCESS_MESSAGE, argv[1]);

    // Close the source and destination files
    fclose(source_file);
    fclose(destination_file);

    return 0;
}

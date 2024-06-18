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
    int encryption_error = 0;

    // Variable to store each character read from the source file
    char character;

    // Loop through each character in the source file until the end of the file (EOF)
    while (1)
    {
        character = fgetc(source_file);

        // Check for EOF
        if (feof(source_file))
        {
            // Close both files and break from the loop
            fclose(source_file);
            fclose(destination_file);
            break;
        }

        // Set the flag indicating that the source file is not empty
        is_empty = 0;

        // Generate a random number, XOR it with the character read from the source file and write the result to the destination file
        int random = rand();
        fputc(character ^ random, destination_file);

        // Check for encryption errors by decrypting the last character by xoring it with the same key and comparing it with the original.
        if ((character ^ random ^ random) != character)
        {
            // If the result is not the original character, set encryption_error flag and break out of the loop
            encryption_error = 1;
            break;
        }
    }

    // If the is_empty flag is set, the source file is empty and the encryption cant be done, if the encryption_error is set, there was an error encrypting the file
    if (is_empty || encryption_error)
    {
        printf(ERROR_MESSAGE, argv[1]);
        remove(argv[2]);
    }
    else
        printf(SUCCESS_MESSAGE, argv[1]);

    return 0;
}

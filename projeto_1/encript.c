#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ERROR_MESSAGE_FORMAT "Encryption of %s failed.\n"

void encrypt_file(const char *input_file, const char *output_file, int seed);
void generateKey(char *key, int length);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        char error_message[100];
        snprintf(error_message, sizeof(error_message), ERROR_MESSAGE_FORMAT, argv[1]);
        printf("%s", error_message);
        return 1;
    }

    encrypt_file(argv[1], argv[2], atoi(argv[3]));
    return 0;
}

void encrypt_file(const char *input_file, const char *output_file, int seed)
{
    srand(seed);

    int input_length = strlen(input_file);
    char key[input_length + 1];

    generateKey(key, input_length);

    // printf("Key: %s\n", key);
}

void generateKey(char *key, int length)
{
    for (int i = 0; i < length; i++)
    {
        key[i] = rand();
    }
    key[length] = '\0';
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MESSAGE "Encryption of %s failed.\n"
#define SUCCESS_MESSAGE "Encryption of %s succeeded.\n"

void encrypt_file(const char *input_file, const char *output_file, const char *key);
void generate_key(char *key, int length);
long get_file_length(const char *input_file);
void dencrypt_file(const char *input_file, const char *key);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <seed>\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[3]);
    long length = get_file_length(argv[1]);
    // printf("Length of the file: %ld bytes\n", length);

    char key[length + 1];
    srand(seed);
    generate_key(key, length);

    printf("Key: %s\n", key);

    encrypt_file(argv[1], argv[2], key); // this is wrong; aba=baa. use *(idx+1)
    dencrypt_file(argv[2], key);
    return 0;
}

void encrypt_file(const char *input_file, const char *output_file, const char *key)
{
    FILE *source_file = fopen(input_file, "r");
    if (source_file == NULL)
    {
        fprintf(stderr, ERROR_MESSAGE, input_file);
        return;
    }

    FILE *destination_file = fopen(output_file, "w");
    if (destination_file == NULL)
    {
        fprintf(stderr, ERROR_MESSAGE, output_file);
        fclose(source_file); // Close the source file before returning
        return;
    }

    int character;
    int key_char;
    int position = 0;

    while ((character = fgetc(source_file)) != EOF && key[position] != '\0')
    {
        key_char = key[position];
        fputc(character ^ key_char, destination_file);
        position++;
    }

    // Check if both files reached EOF or end of key
    if (character == EOF && key[position] == '\0')
    {
        fprintf(stderr, SUCCESS_MESSAGE, input_file);
    }
    else
    {
        fprintf(stderr, ERROR_MESSAGE, input_file);
    }

    fclose(source_file);
    fclose(destination_file);
}

long get_file_length(const char *input_file)
{
    FILE *source_file = fopen(input_file, "r");
    fseek(source_file, 0, SEEK_END);
    long length = ftell(source_file);
    fseek(source_file, 0, SEEK_SET);
    return length;
}

void generate_key(char *key, int length)
{
    for (int i = 0; i < length; i++)
    {
        key[i] = rand();
    }
    key[length] = '\0';
}

void dencrypt_file(const char *input_file, const char *key)
{
    printf("\nFile decrypted\nData:\n");

    FILE *source_file = fopen(input_file, "r");

    int character;
    int key_char;
    int position = 0;

    while ((character = fgetc(source_file)) != EOF && key[position] != '\0')
    {
        key_char = key[position];
        printf("%c", character ^ key_char);
        position++;
    }

    fclose(source_file);
}

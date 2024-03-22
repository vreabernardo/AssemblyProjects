#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MESSAGE "Encryption of %s failed.\n"
#define SUCCESS_MESSAGE "Encryption of %s succeeded.\n"

void encrypt_file(const char *input_file, const char *output_file, const char *key);
void generate_key(char *key, int length, int seed);
long get_file_length(const char *input_file);
void dencrypt_file(const char *input_file, const char *key);
int generateSeed(char *baseSeed);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <seed>\n", argv[0]);
        return 0;
    }

    int seed = generateSeed(argv[3]);

    long length = get_file_length(argv[1]);

    if (length == 0)
    {
        fprintf(stderr, ERROR_MESSAGE, argv[1]);
        // printf("File is empty\n");
        return 0;
    }

    char key[length + 1];
    generate_key(key, length, seed);

    encrypt_file(argv[1], argv[2], key);
    // dencrypt_file(argv[2], key); // check if the file is encrypted correctly
    return 0;
}

void encrypt_file(const char *input_file, const char *output_file, const char *key)
{
    FILE *source_file = fopen(input_file, "r");
    FILE *destination_file = fopen(output_file, "w");

    int character;
    int key_char;
    int position = 0;

    while ((character = fgetc(source_file)) != EOF && key[position] != '\0')
    {
        key_char = key[position];
        fputc(character ^ key_char, destination_file);
        position++;
    }

    if (character == EOF && key[position] == '\0')
    {
        fprintf(stderr, SUCCESS_MESSAGE, input_file);
    }
    else
    {
        fprintf(stderr, ERROR_MESSAGE, input_file);
        // printf("Key is not the same size as the File\n");
    }

    fclose(source_file);
    fclose(destination_file);
}
void generate_key(char *key, int length, int seed)
{
    srand(seed);
    for (int i = 0; i < length; i++)
    {
        key[i] = rand();
    }
    key[length] = '\0';
}

int generateSeed(char *baseSeed)
{
    int seed = 0;

    // baseSeed = seed number + filename -> aba=aab -> fix: [(idx+1)*a for a in argv[3]]
    for (int i = 0; baseSeed[i] != '\0'; i++)
    {
        seed += (baseSeed[i] * (i + 1));
    }
    // printf("Seed: %d\n", seed);
    return seed;
}

long get_file_length(const char *input_file)
{
    FILE *source_file = fopen(input_file, "r");
    fseek(source_file, 0, SEEK_END);  // go to end of file
    long length = ftell(source_file); // get current position on the file
    fclose(source_file);

    // printf("Length of the file: %ld bytes\n", length);
    return length;
}

void dencrypt_file(const char *input_file, const char *key)
{
    printf("File decrypted\nData:\n");

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
    printf("\n");
    fclose(source_file);
}
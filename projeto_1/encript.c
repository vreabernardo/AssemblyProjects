#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MESSAGE "Encryption of %s failed.\n"
#define SUCCESS_MESSAGE "Encryption of %s succeeded.\n"

void encrypt_file(const char *input_file, const char *output_file, int seed);
void generate_key(char *key, int length);
long get_file_length(FILE *file);
void dencrypt_file(const char *input_file, const char *key);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <seed>\n", argv[0]);
        return 1;
    }

    encrypt_file(argv[1], argv[2], atoi(argv[3])); // this is wrong; aba=baa. use *(idx+1)
    return 0;
}

void encrypt_file(const char *input_file, const char *output_file, int seed)
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
        fprintf(stderr, ERROR_MESSAGE, input_file);
        return;
    }

    long length = get_file_length(source_file);
    // printf("Length of the file: %ld bytes\n", length);

    char key[length + 1];
    srand(seed);
    generate_key(key, length);

    printf("Key: %s\n", key);

    int character;
    int character2;

    int position = 0;

    while (1)
    {
        character = fgetc(source_file);
        character2 = key[position];

        if (character == EOF || character2 == '\0')
        {
            if (character == EOF && character2 == '\0')
            {
                fprintf(stderr, SUCCESS_MESSAGE, input_file);
            }
            else
            {
                fprintf(stderr, ERROR_MESSAGE, input_file);
            }
            break;
        }
        else
        {
            fputc(character ^ character2, destination_file);
        }

        position++;
    }

    fclose(source_file);
    fclose(destination_file);

    dencrypt_file(output_file, key);
}

long get_file_length(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
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
    FILE *source_file = fopen(input_file, "r");
    if (source_file == NULL)
    {
        fprintf(stderr, ERROR_MESSAGE, input_file);
        return;
    }

    int character;
    int key_char;

    int position = 0;

    while (1)
    {
        character = fgetc(source_file);
        key_char = key[position];

        if (character == EOF || key_char == '\0')
        {
            if (character == EOF && key_char == '\0')
            {
                printf("\n");
                fprintf(stderr, SUCCESS_MESSAGE, input_file);
            }
            else
            {
                fprintf(stderr, ERROR_MESSAGE, input_file);
            }
            break;
        }
        else
        {
            printf("%c", character ^ key_char);
        }

        position++;
    }

    fclose(source_file);
}

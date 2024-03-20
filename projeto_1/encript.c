#include <stdio.h>
#include <stdlib.h> // for atoi function

void encrypt_file(const char *input_file, const char *output_file, int seed);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s input_file output_file seed\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[3]);
    encrypt_file(argv[1], argv[2], seed);
    return 0;
}

void encrypt_file(const char *input_file, const char *output_file, int seed)
{
}

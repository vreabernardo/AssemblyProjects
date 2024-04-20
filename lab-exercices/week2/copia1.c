#include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *source_file = fopen(argv[1], "r");
    FILE *destination_file = fopen(argv[2], "w");

    int character;

    while ((character = fgetc(source_file)) != EOF)
    {
        fputc(character, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    return 0;
}
#include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *source_file = fopen(argv[1], "r");
    FILE *destination_file = fopen(argv[2], "w");

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0)
    {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char command[100];
    sprintf(command, "stat %s | grep -o \"Size: \\w*\"", argv[1]);

    int status = system(command);

    FILE *file = fopen(argv[1], "r");

    int c;
    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }
    fclose(file);

    return 0;
}

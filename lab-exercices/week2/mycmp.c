#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    int ch1, ch2;

    while (1)
    {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2)
        {
            printf("Files differ at this point: %c != %c\n", ch1, ch2);
            break;
        }

        if (ch1 == EOF || ch2 == EOF)
        {
            if (ch1 == EOF && ch2 == EOF)
            {
                printf("Files are identical.\n");
            }
            else
            {
                printf("Files have different lengths.\n");
            }
            break;
        }
    }
    fclose(file1);
    fclose(file2);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Construct the command string using sprintf
    char command[100];
    sprintf(command, "stat %s | grep -o \"Size: \\w*\"", argv[1]);

    // Execute the command using system
    int status = system(command);

    // Check if the command execution was successful
    if (status == -1) {
        perror("system");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c); // Print the character to standard output
    }
    fclose(file);
    return 0;
}


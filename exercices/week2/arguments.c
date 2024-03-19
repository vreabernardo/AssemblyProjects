#include <stdio.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1; // Return non-zero to indicate error
    }
    
    // Print the provided argument(s)
    printf("%d arguments\n", argc);
    
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    
    return 0; // Return zero to indicate success
}

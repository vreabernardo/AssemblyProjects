#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]){
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Values before swapping: a = %d, b = %d\n", a, b);
    
    swap(&a, &b);

    printf("Values after swapping: a = %d, b = %d\n", a, b);

    return 0;
}


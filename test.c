#include <stdio.h>
#include <stdlib.h>


int main(void) {

    FILE *fptr;

    fptr = fopen("test.txt", "w");

    int num = 3;

    fprintf(fptr, "%d", num);
    fprintf(fptr, "\n");
    fprintf(fptr, "aaa");
    fclose(fptr);
    
    
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "generation.h"

int* generateA(void){

    int *A = (int*)malloc(m * n * sizeof(int)); //define a mxn matrix, don't use multiDarray bc want to train to use pointers. We use particular block shape from the paper.

    if(A == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<m; ++i){
        for (int j = 0; j<n; ++j){
            if (j>(n-m-1)){ //as in the paper I use that A is a bloc matrix
                if (j - (n-m) == i){
                    *(A + i*n + j) = 1;
                }
                else{
                    *(A + i*n + j) = 0;
                }
            }
            else{
                *(A + i*n + j) = rand() % p; //i use rand for pooc, I know it's not secure for crypto
            }
        }

    }
    return A;
}

int* generateV(void){
    int *R = (int*)malloc(n * sizeof(int));

    if(R == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<n; ++i){
        *(R + i) = rand() % p;
    }
    return R;
}

int* generatePermutation(void){ //We represent permutation as an array [a0, a1,...], where ai is in [0,..,n-1], then we map element 0 to element a1, etc. To generate a random permutation we shuffle [0,...,n-1], with Fisher-Yates shuffle.
    int *res = (int*)malloc(n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<n; ++i){ //create the list [0,...,n-1]
            *(res + i) = i;
    }

    for (int i = n-1; i>0; --i){
        int j = rand() % (i+1); // pick a random index between 0 and i.

        int temp = *(res+i); //exhange 
        *(res + i) = *(res + j);
        *(res + j) = temp;
    }

    return res;

}

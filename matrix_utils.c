#include <stdlib.h>
#include <stdio.h>
#include "matrix_utils.h"

void displayMat(int *mat, int rows, int cols){
    for (int i = 0; i<rows; ++i){
        for (int j = 0; j<cols; ++j){
            if (j==(cols-1)){
                printf("%d \n", *(mat + i*cols + j));
            }else{
                printf("%d  ", *(mat + i*cols + j));
            }
        }
    }
}

void displayMatF(int *mat, int rows, int cols, FILE *fptr){
    for (int i = 0; i<rows; ++i){
        for (int j = 0; j<cols; ++j){
            if (j==(cols-1)){
                fprintf(fptr, "%d \n", *(mat + i*cols + j));
            }else{
                fprintf(fptr, "%d  ", *(mat + i*cols + j));
            }
        }
    }
}

void displayVec(int *vec, int rows){
    for (int i = 0; i<rows; ++i){
       printf("%d ", *(vec +i));
    }
}

void displayVecF(int *vec, int rows, FILE *fptr){
    for (int i = 0; i<rows; ++i){
       fprintf(fptr, "%d ", *(vec +i));
    }
}

int* multVecmat(int *vec, int *mat){
    int *res = (int*)malloc(m * sizeof(int)); //output of AR has size m

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<m; ++i){
        int sum = 0;
        for (int j = 0; j<m; ++j){ //we can go only up to m thanks to particular shape of A
            sum += (*(mat + i*n + j) * *(vec + j));
        }
        *(res + i) = sum % p;
        *(res + i) = (*(res + i) + *(vec + i + (n-m))) % p; //we don't forget this, again thanks to shape of A.
    }

    return res;
}

int* multVecMatG (int* vec, int *mat){ //for a general A here.
    int *res = (int*)malloc(m * sizeof(int)); //output of AR has size m

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<m; ++i){
        int sum = 0;
        for (int j = 0; j<n; ++j){ 
            sum += (*(mat + i*n + j) * *(vec + j));
        }
        *(res + i) = sum % p;
    }

    return res;
}

int* permuteVec(int *vec, int *perm){
    int *res = (int*)malloc(n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<n; ++i){
        *(res+i) = *(vec + *(perm+i));
    }
    return res;
}

int* addVec(int *vec1, int *vec2){
    int *res = (int*)malloc(n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<n; ++i){
        *(res + i) = *(vec1 + i) + *(vec2 + i);
    }

    return res;
}

int* multVecC(int *vec, int c){
    int *res = (int*)malloc(n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<n; ++i){
        *(res + i) = (c * *(vec+i)) % p;
    }

    return res;
}

int* inversePerm(int *perm){
    int *res = (int*)malloc(n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i=0; i<n; ++i){
        *(res + *(perm + i)) = i;
    }

    return res;
}

int* permMat(int* mat, int* perm){
    int *res = (int*)malloc(m * n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i<m; ++i){
        for (int j = 0; j<n; ++j){
            *(res + i*n + j) = *(mat + i*n + *(perm + j));
        }
    }

    return res;
}


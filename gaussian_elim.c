#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gaussian_elim.h"
#include "mod_utils.h"
#include "generation.h"
#include "matrix_utils.h"

void swapRows(int* mat, int r1, int r2){
    for (int j = 0; j<n; ++j){
        int temp = *(mat + r1*n + j);
        *(mat + r1*n + j) = *(mat + r2*n + j);
        *(mat + r2*n + j) = temp;
    }
}

int* gaussElim(int *mat){

    int *res = (int*)malloc(m * n * sizeof(int));

    if(res == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i=0; i<m; ++i){
        for (int j=0; j<n; ++j){
            *(res + i*n + j) = *(mat + i*n + j);
        }
    }

    for (int i = 0; i<m; ++i){ //we loop on each rows

        if (*(res + i*n + i) == 0){ // if diagonal element is 0, we swap rows to get a non 0 one (avoid inverse of 0)
            for (int k = i+1; k<m; ++k){
                if (*(res + k*n + i) != 0){
                    swapRows(res, i, k); //find a non 0, swap rows
                    break;
                }
            }
        }
        
        int inv = mod_inverse(*(res + i*n + i));
        if (inv == -1){
            printf("not invertible, singular A mod p\n");
            return res;
        }

        for (int j = 0; j<n; ++j){ //mutliply the whole row by the inverse, making the diag element 1
            *(res + i*n + j) = (*(res + i*n + j) * inv) % p;
        }

        for (int k = 0; k<m; ++k){ //make rest of the column 0
            if (k != i){
                int factor = *(res + k*n + i);
                for (int j = 0; j<n; ++j){
                    *(res + k*n + j) = (*(res + k*n + j) - factor * *(res + i*n + j)) % p;
                    if (*(res + k*n + j) < 0) *(res + k*n + j) += p;
                }
            }
        }

    }

    return res;
}

int* findKernel(int* rref) { //adapted from ChatGPT stuff.
    int freeVars[n];  // To keep track of which variables are free
    int pivotVars[n]; // To keep track of which are pivot variables

    for (int i = 0; i < n; i++) {
        freeVars[i] = 0;
        pivotVars[i] = 0;
    }

    // Identify pivot and free variables
    int row = 0;
    for (int col = 0; col < n; col++) {
        if (row < m && *(rref + row * n + col) == 1) {
            pivotVars[col] = 1;  // Mark as pivot variable
            row++;
        } else {
            freeVars[col] = 1;   // Mark as free variable
        }
    }

    // Find the first free variable and generate a kernel vector
    int* kernelVector = (int*)malloc(n * sizeof(int)); 

    if(kernelVector == NULL){
        printf("could not allocate memory");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        *(kernelVector + i) = 0; 
    }

    // Construct the kernel for the first free variable
    for (int freeCol = 0; freeCol < n; freeCol++) {
        if (freeVars[freeCol]) {
            // Set the free variable to 1 (its basis vector)
            kernelVector[freeCol] = 1;

            // Now express pivot variables in terms of this free variable
            for (int pivotCol = 0; pivotCol < n; pivotCol++) {
                if (pivotVars[pivotCol]) {
                    // Row corresponding to pivotCol
                    int rowForPivot = pivotCol; // This works because matrix is in RREF
                    *(kernelVector + pivotCol) = (p - *(rref +rowForPivot * n + freeCol)) % p;
                }
            }
            break;  // We only want to return one kernel vector
        }
    }

    return kernelVector;
}

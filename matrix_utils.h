#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "constants.h"

void displayMat(int *mat, int rows, int cols); //function to print a give matrix

void displayVec(int *vec, int rows); //print a vector

int* multVecmat(int *vec, int *mat); //multiply matrix with vector, given a matrix of the shape from the paper A = [A'|I] (a bit more efficient than normal mult)

int* permuteVec(int *vec, int *perm); //apply a permuation to a vector

int* addVec(int *vec1, int *vec2); //add 2 vectors together

int* multVecC(int *vec, int c); //multiply a vector by a constant

int* multVecMatG (int* vec, int *mat); //mutliply matrix and vector for any matrix

int* inversePerm(int *perm); //find the inverse of a given permutation
 
int* permMat(int* mat, int* perm); //apply permutation to a matrix, i.e permutes the columns

void displayMatF(int *mat, int rows, int cols, FILE *fptr); //to write matrix into a file

void displayVecF(int *vec, int rows, FILE *fptr); //to write vector into a file

#endif

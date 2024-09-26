#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generation.h"
#include "matrix_utils.h"
#include "mod_utils.h"
#include "gaussian_elim.h"
#include "constants.h"

int main(void){
    srand(time(0));

    FILE *fptr;

    fptr = fopen("results.txt", "w");

    if(fptr == NULL){
        printf("could not open file");
        exit(1);
    }

    //First, both parties agree on A
    int *A = generateA();
    fprintf(fptr, "--- Generated A is ---\n");
    displayMatF(A, m ,n, fptr);


    //Then let's compute V (that both prover and verifier know) and pi (only prover knows it)

    int *A_rref = gaussElim(A); //we want to find a V in kernel so we do gaussian elimination.

    int *K = findKernel(A_rref); // we get a vector in the kernel

    int *mult = multVecMatG(K, A); // we check it's indeed in the kernel

    for (int i=0; i<m; ++i){
        if (*(mult + i) == 0) continue;
        else{
            printf("Not in the Kernel");
            break;
        }
    }

    //Now let's generate a random permutation pi, and take V as V_pi-1 (and so V_pi = K is in the kernel)
    int *pi = generatePermutation();
    fprintf(fptr, "--- Permutation pi is ---\n");
    int *inv_pi = inversePerm(pi);
    displayVecF(pi, n, fptr);

    int *V = permuteVec(K, inv_pi); //This is the V such that V_pi = K is in the Kernel, the prover knows it.
    fprintf(fptr, "\n--- V such that V_pi is in kernel of A is ---\n");
    displayVecF(V, n, fptr);

    free(A_rref);
    free(K);
    free(mult);

    fprintf(fptr, "\n\n ---------------------------- Starting protocol ---------------------------- \n");

    int *R = generateV();
    int *sig = generatePermutation();
    fprintf(fptr, "\n--- P chooses a random vector R and a random permutation sig --- \n");
    fprintf(fptr, "R is \n");
    displayVecF(R, n, fptr);
    fprintf(fptr, "\nsig is \n");
    displayVecF(sig, n, fptr);

    fprintf(fptr, "\n\n--- P sends hashed (sig, AR) and (pi o sig, R_sig to V) --- \n");

    int *AR = multVecmat(R, A);
    fprintf(fptr, "AR is \n");
    displayVecF(AR, m, fptr);
    int *R_sig = permuteVec(R, sig);
    fprintf(fptr, "\nR_sig is \n");
    displayVecF(R_sig, n, fptr);

    int *piosig = permuteVec(pi, sig);
    fprintf(fptr, "\npi o sig is\n");
    displayVecF(piosig, n, fptr);

    fprintf(fptr, "\n\n --- V chooses a random c in [0,p) ---\n");

    int c = rand() % p;
    fprintf(fptr, "c is %d\n", c);

    fprintf(fptr, "\n --- P sends W = R_sig + cVpiosig ---\n");
    int *cV_pi_sig = multVecC(permuteVec(permuteVec(V, pi), sig), c); //Here P knows pi so he can do this transformation
    int *W = addVec(R_sig, cV_pi_sig);
    fprintf(fptr, "W is \n");
    displayVecF(W, n, fptr);

    fprintf(fptr, "\n\n--- P now reveals sig or piosig. If P revealed piosig, V checks that W - cV_pi_sig = R_sig --- \n");

    int *mcV_pisig = multVecC(cV_pi_sig, -1); //V as vector V and piosig, so he can compute it (I reuse the one from P not to use have the same vector multiple times.)

    int *fin = addVec(W, mcV_pisig);

    fprintf(fptr, "W - cVpiosig is \n");
    displayVecF(fin, n, fptr);
    fprintf(fptr, "\nR_sig is\n");
    displayVecF(R_sig, n, fptr);

    fprintf(fptr, "\n\n--- V checks that both are equal --- \n");

    int equal = 1;

    for (int i = 0; i<n; ++i){ //check they are indeed equal
        if (*(fin + i) == *(R_sig + i)) continue;
        else{
            printf("Not equal\n");
            equal = 0;
            break;
        }
    }
    if (equal == 1) fprintf(fptr, "\n------------- They are indeed equal so V can send a positive answer on wether P knows pi or not -------------\n");
    else fprintf(fptr, "\n---------------------------- They are not equal ----------------------------\n");

    fprintf(fptr, "\n\n--- Say now that P revealed sig. V wants to check that A_sigW = AR --- \n");

    int *A_sig = permMat(A, sig);
    fprintf(fptr, "A_sig is \n");
    displayMatF(A_sig, m, n, fptr);


    int *AsigW = multVecMatG(R_sig, A_sig);

    fprintf(fptr, "A_sigW is \n");
    displayVecF(AsigW, m, fptr);
    fprintf(fptr, "\nAR is \n");
    displayVecF(AR, m, fptr);

    fprintf(fptr, "\n--- V now checks they are equal ---\n");

    equal = 1;

    for (int i = 0; i<m; ++i){ //check if equal
        if (*(AsigW + i) == *(AR + i)) continue;
        else{
            printf("%d", *(AR+i));
            printf("Not equal\n");
            equal = 0;
            break;
        }
    }

    if (equal == 1) fprintf(fptr, "\n------------- They are equal and so V can output a positive answer on wether P knows pi or not -------------");
    else fprintf(fptr, "\nThey are not equal ---");


    free(V);
    free(R);
    free(sig);
    free(AR);
    free(R_sig);
    free(piosig);
    free(cV_pi_sig);
    free(W);
    free(mcV_pisig);
    free(fin);
    free(A_sig);
    free(AsigW);

    fclose(fptr);
    
    return 0;
}

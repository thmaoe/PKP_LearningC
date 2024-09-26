#include "mod_utils.h"


int mod_inverse(int a){
    int t = 0, newt = 1, r = p, newr = a;

    while(newr != 0){
        int quotient = r / newr;
        int temp_t = t;
        t = newt;
        newt = temp_t - quotient * newt;

        int temp_r = r;
        r = newr;
        newr = temp_r - quotient * newr;
    }

    if (r>1){
        return -1;
    }
    if (t < 0){
        t += p;
    }

    return t;
}


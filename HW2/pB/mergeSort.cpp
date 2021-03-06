#include<iostream>
#include<algorithm>
using namespace std;

void Merge (int* A, int p, int q, int r){
    int n1 = q-p+1 , n2 = r-q;
    int L[n1+1], R[n2+1];
    int i,j;
    for (i=0; i<n1; ++i)
        L[i] = A[p+i];
    for (j=0; j<n2; ++j)
        R[j] = A[q+j+1];
    //copy(A, A+n1, L);
    //copy(A+n1+1, A+r, R);
    R[n2] = L[n1] = INT32_MAX;
    i = j = 0;
    for (int k = p; k <=r; ++k){
        if (L[i] < R[j]){
            A[k] = L[i];
            ++i;
        }else{
            A[k] = R[j];
            ++j;
        }
    }
}

void mergeSort (int* A, int p, int r){
    if (p<r){
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        Merge(A, p, q, r);
    }
}
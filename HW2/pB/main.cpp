#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

void Merge (int* A, int p, int q, int r, long int& counter){
    int n1 = q-p+1 , n2 = r-q; //n1, n2是子陣列的真實物件個數
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
            counter += (n1-i);
            ++j;
        }
    }
}

void mergeSort (int* A, int p, int r, long int& counter){
    if (p<r){
        int q = (p+r)/2;
        mergeSort(A, p, q, counter);
        mergeSort(A, q+1, r, counter);
        Merge(A, p, q, r, counter);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    cin >> n;
    bool odd = (n%2);
    const int vaLength = (odd ? (n/2+1) : (n/2) );
    const int vbLength = (n/2);
    int va[vaLength];
    int vb[vbLength];

    for (int i=0; i<(n/2); ++i){
        cin >> va[i];
        cin >> vb[i];
    }
    if (odd){
        cin >> va[n/2];
    }

    long int countera(0), counterb(0);
    mergeSort(va, 0, vaLength-1, countera);
    mergeSort(vb, 0, vbLength-1, counterb);
    long int counter = countera + counterb;
    
    bool flag = true;
    for(int i=0; i<vbLength-1; i++){
        if(vb[i]<va[i] || vb[i]>va[i+1]){
            flag = false;
            break;
        }
    }
    if(vb[vbLength-1]<va[vbLength-1])
        flag = false;
    if(odd && (vb[vbLength-1]>va[vbLength]))
        flag = false;
    
    cout << (flag? "yes":"no") << endl << counter;
    return 0;
}
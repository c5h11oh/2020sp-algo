#include <iostream>
#include <algorithm>
using namespace std;

int main (){
    int sumBogay(0), sumAserf(0), N, K, L;

    cin >> N;
    int *Narray = new int[N];
    cin >> K;
    L = N/K;
    int *Larray = new int[L];
    for (int i=0; i<N; ++i) cin >> Narray[i];
        
    if (K == 1){
        for (int i=0; i<L; ++i)
            Larray[i] = Narray[i];
    }
    else {
        for (int i=0; i<L; ++i) {
            Larray[i] = 0;
            for( int j=0; j<K; ++j)
                Larray[i] += Narray[K*i+j]; 
        }
    }

    int **dp = new int*[L];
    for (int i=0; i<L; ++i)
        dp[i] = new int[L];

    for (int l=0; l<L; ++l)
        dp[l][l] = Larray[l];
    for (int l=0; l<L-1; ++l)
        dp[l][l+1] = max(Larray[l],Larray[l+1]);
    for (int l=2; l<L; ++l){
        for (int i=0; i<L-l; ++i){
            dp[i][i+l] = max(Larray[i]+min(dp[i+1][i+l-1],dp[i+2][i+l]), Larray[i+l]+min(dp[i][i+l-2],dp[i+1][i+l-1]));
        }
    }

    
    if (L <= 2){
        sumBogay = max(Larray[0], Larray[1]);
        sumAserf = min(Larray[0], Larray[1]);

    }else{
        sumBogay = dp[0][L-1];
        bool flag = (Larray[0]+min(dp[1][L-2],dp[2][L-1]) > Larray[L-1]+min(dp[0][L-3],dp[1][L-2]));
        sumAserf = (flag ? dp[1][L-1] : dp[0][L-2]);
    }
    
    if (sumBogay == sumAserf){
        cout << "TIE" << endl;
    }else if (sumBogay > sumAserf){
        cout << "Bogay" << endl;
    }else{
        cout << "aserf18766" << endl;
    }
    cout << sumBogay << " " << sumAserf << endl;
    

    delete[] Larray, Narray;
    for (int i=0; i<L; ++i) delete[] dp[i];
    delete dp;
    return 0;
}
#include <iostream>
using namespace std;

inline void yes(){
    cout << "yes" << endl;
}

inline void no(){
    cout << "no" << endl;
}

int main () {
    //prevent slow io
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //initiate
    int j, k; //initially, N=j=k
    long int sum = 0, D;
    cin >> j >> D;
    const int N = j--;
    k = j;
    int M[N];
    for (int i=0; i<N; i++) cin >> M[i];
    sum+=M[k];

    //judgement
    while( k > 0 ){
        if( sum == D ){
            yes();
            return 0;
        }
        else if( sum < D)
            sum+=M[--k];
        else{
            sum-=M[j--];
        }
    }
    ( k==0 && sum==D ) ? (yes()) : (no()) ;
    return 0;
}
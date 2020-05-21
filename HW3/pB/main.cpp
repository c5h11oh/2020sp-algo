#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int mod = 1000000007;

unsigned long long int** createModPowerTable(){
    unsigned long long int** table = new unsigned long long int*[4];
    for (int i=0; i<4; ++i)
        table[i] = new unsigned long long int[10]{0};

    for (int i=0; i<4; ++i) table[i][0] = 1;
    
    // for i==0
        for (int j=1; j<10; ++j){
            table[0][j] = table[0][j-1] *2;
        }
        table[1][1] = table[0][9]*2;
    // for i>=1 
    for (int i=1; i<4; ++i){
        for (int j=2; j<10; ++j){
            table[i][j] = (table[i][j-1] * table[i][1])%mod;
        }
        if(i!=3) table[i+1][1] = (table[i][9] * table[i][1])%mod;
    }

    return table;
}


int main (){
    int N, M;
    //const int mod = 1000000007;
    cin >> N >> M;
    int input[N];
    for (int i=0; i<N; ++i) cin >> input[i];
    
    //create table
    unsigned long long int** table = createModPowerTable();

    vector<int> pair[N];
    for (int i=0; i<N-1; ++i){
        for (int j=i+1; j<N; ++j){
            if(abs(input[i]-input[j])<=M)
                pair[i].push_back(j);
        }
    }
    
    int ans[N+1] = {0};
    int power(0), subsm;
    int pp[4]{0};
    for (int i=N-2; i>=0; --i){
        if(pair[i].empty()){
            ans[i] = (ans[i+1]+ans[i+1])%mod;
        }else{
            int sum = (ans[i+1]+ans[i+1])%mod;
            for (int j:pair[i]){
                power = (N-1-j);
                subsm = 1;
                for(int k=0; k<4; ++k){
                    pp[k] = power%10;
                    power/=10;
                }
                for(int k=0; k<4; ++k){
                    subsm = (subsm * table[k][pp[k]])%mod;
                }
                sum = (((sum + ans[j+1])%mod + subsm)%mod -ans[j]+mod)%mod;
            }
                
            ans[i] = sum; 
        }
    }
    
    cout << ans[0];
    
    //delete table
    for (int i=0; i<4; ++i) delete[] table[i];
    delete table;

    return 0;
}

// int main (){
//     int** table = createModPowerTable();
//     cout << table[0][2];
// }
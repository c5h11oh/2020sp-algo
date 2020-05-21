#include <iostream>
#include <vector>
using namespace std;

//矩陣相乘（同矩陣相乘）
unsigned long long int** matrixPower(unsigned long long int** input){
    unsigned long long int** output = new unsigned long long int*[2];
    for ( int i=0; i<2; i++)
        output[i] = new unsigned long long int[2];
    for ( int i=0; i<2; i++){
        for ( int j=0; j<2; j++){
            output [i][j] = 0;
            for ( int k=0; k<2; k++)
                output [i][j] += input[i][k] * input [k][j];
            output [i][j] %= (long long)1000000007;
        }
    }
    return output;
}

//矩陣相乘（不同矩陣相乘）
unsigned long long int** matrixPower(unsigned long long int** input1, unsigned long long int** input2){
    unsigned long long int** output = new unsigned long long int*[2];
    for ( int i=0; i<2; i++)
        output[i] = new unsigned long long int[2];
    for ( int i=0; i<2; i++){
        for ( int j=0; j<2; j++){
            output [i][j] = 0;
            for ( int k=0; k<2; k++)
                output [i][j] += input1[i][k] * input2 [k][j];
            output [i][j] %= (long long)1000000007;
        }
    }
    return output;
}

//十進位轉二進位
void toBinaryReversed(unsigned long long int n,  int *bin){
    int i = 0;
    while(n > 0 && i < 32){
        *bin = n % 2;
        n/=2;
        i++;
        bin++;
    }
}

 int main (){
    /*矩陣乘法測試
    unsigned long long int matrix1[2][2] = {{17853,20148},{90187,473843}};
    unsigned long long int matrix2[2][2] = {{25536,901784},{48792,2789571}};
    unsigned long long int* pointer1[2] = {matrix1[0], matrix1[1]};
    unsigned long long int* pointer2[2] = {matrix2[0], matrix2[1]};
    unsigned long long int** matrix3 = matrixPower(pointer1, pointer2);
    for (int i=0; i<2; i++)
        for (int j=0;j<2;j++)
            cout << matrix3[i][j] << "\t";
    */

    unsigned long long int a1, a2, power = 539, maxPower = 0; //power=題目輸入的n
    int powerbin[32] = {0}; //要乘的次方數轉二進位反序
    unsigned long long int **input = new unsigned long long int*[2];
    for (int i=0; i<2; i++)
        input[i] = new unsigned long long int[2];
    vector<unsigned long long int**> output;
    
    cin >> a1 >> a2;
    cin >> input[0][0] >> input[0][1]; //題目的x,y
    //input[0][0] = input[0][1] = 1;
    cin >> power; //題目的n
    
    input[1][0] = 1; input[1][1] = 0; 
    output.push_back(input);
    
    power = power-2; //真正要乘的次方數
    toBinaryReversed(power, powerbin); //要乘的次方數轉二進位（powerbin[0]表2^0位的值）
    
    for ( int i=31; i>=0; i--){
        if (powerbin[i]==1){
            maxPower = i;
            break;
        }
    }

    for ( int i=0; i<maxPower; i++){
        unsigned long long int **temp = matrixPower(output.back());
        output.push_back(temp);
    }

    //印出乘n-2次的結果
    
        //建立初始output
    unsigned long long int **result = new unsigned long long int*[2];
    for (int i=0; i<2; i++){
        result[i] = new unsigned long long int[2];
        for (int j=0; j<2; j++)
            result[i][j] = output[maxPower][i][j];
    }
        //相乘
    for (int i=maxPower-1; i>=0; i--){
        if (powerbin[i]==1)
            result = matrixPower(result, output[i]);
    }

        //cout輸出
    cout << (a2 * result[0][0] + a1 * result[0][1])%1000000007 << endl;

    return 0;
}


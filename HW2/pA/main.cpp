#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n(0);
    cin >> n;
    vector<vector<int>> input(n, vector<int>(2,0));
    for (int i=0; i<n; i++){
        cin >> input[i][0];
        input[i][1] = i;
    }
    sort(input.begin(), input.end());
    int maxNum = 0;
    for(int i=0; i<n; i++){
        maxNum = max(maxNum,input[i][1] - i);
    }
    cout << maxNum << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

void Print_and_Sort(int thisNode, int parentNode, vector<vector<int>>& edgeList){
    // Print
    cout << thisNode << " ";
    sort(edgeList[thisNode].begin(), edgeList[thisNode].end(), greater<int>());
    for (int adjNode: edgeList[thisNode]) {
        if (adjNode == parentNode) continue;
        Print_and_Sort(adjNode, thisNode, edgeList);
    }
}

int main () {
    int N = 0;
    int temp[] = {0,0};
    cin >> N;
    vector<vector<int>> vec(N+1);
    for(int i=0; i<N-1; ++i){
        cin >> temp[0] >> temp[1];
        vec[temp[0]].push_back(temp[1]);
        vec[temp[1]].push_back(temp[0]);
    }
    Print_and_Sort(N, 0, vec);

    return 0;
}
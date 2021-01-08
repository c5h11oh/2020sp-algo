/* HW5 pB Lava */
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

void judge(vector<vector<char>>& map, queue<pair<int,int>>& q, int& currentAmountOfX, int& nextRoundCount);
void fire(vector<vector<char>>& map, queue<pair<int,int>>& q, const pair<int,int>& pos, int& currentAmountOfX, int& nextRoundCount);

int main() {
    int N, M, K;
    string s;
    std::stringstream ss;
    //輸入地圖
    cin >> N >> M >> K;
    vector<vector<char>> map(N+2);
    for (int i=0; i<N+2; ++i) map[i]=vector<char>(M+2);
    for (int i=1; i<N+1; ++i){
        ss.clear();
        cin >> s;
        ss << s;
        for (int j=1; j<M+1; ++j){
            map[i][j] = ss.get();
        }
    }
    for(int i=0; i<M+2; ++i) {map[0][i] = map[N+1][i] = 'O';}
    for(int i=1; i<N+1; ++i) {map[i][0] = map[i][M+1] = 'O';}
    //找start和總C數
    pair<int,int> start;
    int totalAmountOfC = 0;
    for (int i=1; i<N+1; ++i){
        for (int j=1; j<M+1; ++j){
            if(map[i][j] == 'L'){
                start.first=i; start.second=j;
            }
            if(map[i][j] == 'C') ++totalAmountOfC;
        }
    }
    //BFS
        //counters
        int round = 0;
        int currentAmountOfX = 0;
        int nextRoundCount = 1;
        //int totalAmountOfC 已被定義
    queue<pair<int,int>> q;
    q.push(start);
    while (round < K){
        if(totalAmountOfC==currentAmountOfX) break;
        const int thisRoundCount = nextRoundCount;
        nextRoundCount = 0;
        for (int i=0; i<thisRoundCount; ++i){
            judge(map, q, currentAmountOfX, nextRoundCount);
        }
        ++round;
    }
    //Print
    for (int i=1; i<N+1; ++i){
        for (int j=1; j<M+1; ++j){
            cout << map[i][j];
        }
        cout << endl;
    }
    return 0;
}

void judge(vector<vector<char>>& map, queue<pair<int,int>>& q, int& currentAmountOfX, int& nextRoundCount){
    int x = q.front().first;
    int y = q.front().second;
    fire(map,q,pair<int,int>(x-1,y),currentAmountOfX,nextRoundCount);
    fire(map,q,pair<int,int>(x+1,y),currentAmountOfX,nextRoundCount);
    fire(map,q,pair<int,int>(x,y-1),currentAmountOfX,nextRoundCount);
    fire(map,q,pair<int,int>(x,y+1),currentAmountOfX,nextRoundCount);
    q.pop();
}
void fire(vector<vector<char>>& map, queue<pair<int,int>>& q, const pair<int,int>& pos, int& currentAmountOfX, int& nextRoundCount){
    if(map[pos.first][pos.second]=='C'){
        map[pos.first][pos.second]='X';
        ++currentAmountOfX;
        q.push(pos);
        ++nextRoundCount;
    }
}
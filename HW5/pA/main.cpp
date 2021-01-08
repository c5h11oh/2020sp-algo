#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
using namespace std;


int main(){
    int N;
    cin >> N;
    int VertexMaxWeight[N+1];
    int Father[N+1];
    for(int i=0; i<=N; ++i) { Father[i]=-1; VertexMaxWeight[i]=INT32_MAX;}
    vector<pair<int, int>> adjList[N+1];
    for (int i=0; i<N-1; ++i){
        int s, e, w;
        cin >> s >> e >> w;
        adjList[s].push_back(pair<int,int>(e,w));
        adjList[e].push_back(pair<int,int>(s,w));
    }
    int start, end;
    cin >> start >> end;
    bool found = false;
    queue<int> q;
    q.push(start);
    while(!found){
        for (auto p:adjList[q.front()]){
            if(p.first==end){
                VertexMaxWeight[p.first] = min(p.second, VertexMaxWeight[q.front()]);
                found = true;
                break;
            }
            else if(p.first!=Father[q.front()]){
                q.push(p.first);
                Father[p.first] = q.front();
                VertexMaxWeight[p.first] = min(p.second, VertexMaxWeight[q.front()]);
            }
        }
        q.pop();
    }
    cout << VertexMaxWeight[end];
}
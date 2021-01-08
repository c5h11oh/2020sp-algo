#include <iostream>
#include <queue>
#include <list>
using namespace std;
const long INF = __LONG_MAX__/2-100;
typedef pair<long, int> thePair; //first=weight; second=destination/node

long Dijkstra(int N, int start, int end, list<thePair> adjList[]);

int main(){
    int N, M;
    cin >> N >> M;
    int Nodes[4];
    for(int i=0; i<4; ++i) cin >> Nodes[i];
    list<thePair> adjList[N+1];
    int ui, vi; long wi;
    for(int i=0; i<M; ++i){
        cin >> ui >> vi >> wi;
        adjList[ui].push_back(make_pair(wi, vi));
        adjList[vi].push_back(make_pair(wi, ui));
    }
    long result = 0;
    for (int i=0; i<4; ++i) result+=Dijkstra(N, Nodes[i], Nodes[(i+1)%4], adjList);
    cout << result;
    return 0;
}

long Dijkstra(int N, int start, int end, list<thePair> adjList[]){
    vector<long> dist(N+1, INF);
    dist[start] = 0;
    //int parentNode[N+1];
    //for(int i=0; i<N+1; ++i) parentNode[i] = -1;
    priority_queue<thePair, vector<thePair>, greater<thePair>> pq;
    pq.push(make_pair(0, start));
    while(pq.top().second!=end){
        long nodeDist = pq.top().first;
        int node = pq.top().second;
        for(auto e: adjList[node]){
            if(nodeDist + e.first < dist[e.second]){
                dist[e.second] = nodeDist + e.first;
                pq.push(make_pair(dist[e.second], e.second));
            }
        }
        pq.pop();
    }
    return dist[end];
}
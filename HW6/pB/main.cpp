#include <iostream>
#include <set>
#include <map>
using namespace std;
const long INF = __LONG_MAX__/2-100;

int RelaxReturnMinDistNode(set<int>& unfinished, int node, map<int, long> adjMap[], long dist[], int parentNode[]){
    long minNodeDist = INF;
    int minNode = -1;
    for (auto it:adjMap[node]){
        //auto it = adjMap[node].find(i);
        if(unfinished.find(it.first)!=unfinished.end() && dist[node]+it.second<dist[it.first]){
            dist[it.first]=dist[node]+it.second;
            parentNode[it.first]=node;
        }
    }
    for (int i:unfinished){
        if(dist[i]<minNodeDist){
            minNodeDist = dist[i];
            minNode = i;
        }
    }
    return minNode;
}

long Dijkstra(int N, int start, int end, map<int, long> adjMap[]){
    long dist[N+1];
    int parentNode[N+1];
    set<int> unfinished;
    for (int i=1; i<N+1; ++i){
        unfinished.insert(i);
        dist[i]=INF;
        parentNode[i]=-1;
    }
    unfinished.erase(start);
    dist[start]=0;
    int currentNode = start;
    do{
        currentNode = RelaxReturnMinDistNode(unfinished, currentNode, adjMap, dist, parentNode);
        unfinished.erase(currentNode);
    }while(currentNode!=end);
    return dist[end];
}

int main(){
    //Dijkstra
    int N, M;
    cin >> N >> M;
    int Nodes[4]; //cin >> H >> S1 >> S2 >> C;
    for(int i=0; i<4; ++i) cin >> Nodes[i];
    map<int, long> adjMap[N+1];
    // long** adjMat = new long* [N];
    // for (int i=0; i<N; ++i) adjMat[i] = new long[N];
    // long adjMat[N][N];
    // for (int i=0; i<N; ++i){
    //     for (int j=0; j<N; ++j)
    //         adjMat[i][j] = INF;
    // }
    int ui, vi; long wi;
    for (int q=0; q<M; ++q){
        cin >> ui >> vi >> wi;
        adjMap[ui][vi] = wi;
        adjMap[vi][ui] = wi;
    }
    //for (int i=0; i<N; ++i) adjMat[i][i]=0;
    long result = 0;
    for (int i=0; i<4; ++i) result=result+Dijkstra(N, Nodes[i], Nodes[(i+1)%4], adjMap);
    cout << result;
    // for (int i=0; i<N; ++i) delete[] adjMat[i];
    // delete[] adjMat;
    return 0;
}
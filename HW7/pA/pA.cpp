#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <map>
using namespace std;
const int max_capacity = 1001;
typedef map<int, int> EdgeMap;

//Ford-Fulkerson
class FordFulkerson{
public:
    FordFulkerson(int n): numOfNode(n){
        adjList.resize(n+1);
    }
    void addDoubleAdj(int u, int v, int w);
    void addSingleAdj(int u, int v, int w);
    int performFordFulkerson(int s, int t);
    int getFlow(){return flow;}
private:
    int numOfNode;
    int flow = 0;
    vector<EdgeMap> adjList;
    bool BFS_Search(vector<EdgeMap>&, bool*, int*, int*, int, int);
};

void FordFulkerson::addDoubleAdj(int u, int v, int w){
    if(adjList[u].count(v)){
        adjList[u][v] += w;
    }else{ adjList[u][v] = w;}
    
    if(adjList[v].count(u)){
        adjList[v][u] += w;
    }else{ adjList[v][u] = w;}
}

void FordFulkerson::addSingleAdj(int u, int v, int w){
    if(adjList[u].count(v)){
        adjList[u][v] += w;
    }else{ adjList[u][v] = w;}
}

bool FordFulkerson::BFS_Search(vector<EdgeMap>& residualNetwork, bool* visited, int* predecessor, int* capacity, int s, int t){
    //initial setup
    for (int i=0; i<numOfNode+1; ++i){
        visited[i] = false;
        predecessor[i] = -1;
        capacity[i] = 0;
    }
    //bfs
    queue<int> q;
    q.push(s);
    capacity[s] = max_capacity;
    visited[s] = true;
    while(!q.empty()){
        int current = q.front();
        for(auto we : residualNetwork[current]){
            if(!visited[we.first] && we.second>0){
                visited[we.first] = true;
                predecessor[we.first] = current;
                capacity[we.first] = min(capacity[current], we.second);
                q.push(we.first);
            }
        }
        q.pop();
    }
    return visited[t];
}

int FordFulkerson::performFordFulkerson(int s, int t){
    vector<EdgeMap> residualNetwork = adjList;
    bool visited[numOfNode+1];
    int predecessor[numOfNode+1];
    int capacity[numOfNode+1];
    while(BFS_Search(residualNetwork, visited, predecessor, capacity, s, t)){
        flow += capacity[t];
        for(int current = t; current != s; current = predecessor[current]){
            if(current == -1){
                cout <<"Error! current == -1. \n";
                break;
            }
            auto it1 = residualNetwork[predecessor[current]].find(current);
            auto it2 = residualNetwork[current].find(predecessor[current]);
            if(it1==residualNetwork[predecessor[current]].end()) {
                cout << "Error! Forward Item not found.\n current = " << current << ", predecessor = " << predecessor[current] << "\n";
                break;
            }
            if(it2==residualNetwork[current].end()) {
                cout << "Error! Backward Item not found.\n current = " << current << ", predecessor = " << predecessor[current] << "\n";
                break;
            }
            it1->second -= capacity[t];
            it2->second += capacity[t];
        }
    }
    return flow;
}

int main (){
    int N, M, s, t; 
    cin >> N >> M >> s >> t;
    FordFulkerson ff(N);
    for (int i=0; i<M; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        ff.addDoubleAdj(u, v, w);
    }
    int flow = ff.performFordFulkerson(s, t);
    cout << flow;

    return 0;
}
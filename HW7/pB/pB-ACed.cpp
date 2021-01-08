#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

typedef vector<map<int, int>> Edges; //Edges[u][v] = w; u to v weight w.
//For an edge: first=next node; second=weight.

struct Graph{
    Graph(){}
    Graph(int n): numOfNodes(n){
        edges.resize(n+1);
    }
    void reset(int n){
        numOfNodes = n;
        for(auto a : edges) a.clear();
        edges.clear();
        edges.resize(n+1);
    }
    void addSingleEdge(int u, int v, int w){
        //if(edges[u].count(v)) edges[u][v]+=w;
        //else 
        edges[u][v]=w;
        if(!edges[v].count(u)) edges[v][u] = 0; 
    }
    void addDoubleEdge(int u, int v, int w){
        //if(edges[u].count(v)) edges[u][v]+=w;
        //else 
        edges[u][v]=w;
        //if(edges[v].count(u)) edges[v][u]+=w;
        //else 
        edges[v][u]=w;
    }
    int numOfNodes = 0;
    Edges edges;
    ~Graph(){}
};

//Ford-Fulkerson
class FordFulkerson{
public:
    FordFulkerson(Graph& gr, int s, int t):graph(gr), residual(gr), s(s), t(t){
        PerformFordFulkerson();
    }
    int getFlow(){return flow;}
    int getCutCapacity(){return cut_capacity;}
    void PerformFordFulkerson();
private:
    int s, t;
    const int max_capacity = 1e5;
    int flow = 0;
    int cut_capacity = 0;
    Graph graph, residual;
    bool BFS_Search(bool*, int*, int*, int, int);
    //int FindCutCapacity();
};

bool FordFulkerson::BFS_Search(bool* visited, int* predecessor, int* capacity, int s, int t){
    //initial setup
    for (int i=0; i<graph.numOfNodes+1; ++i){
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
        for(auto we : residual.edges[current]){
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

// int FordFulkerson::FindCutCapacity(){
//     cut_capacity = 0;
//     bool visited[residual.numOfNodes+1];
//     for(int i=0; i<residual.numOfNodes+1; ++i) visited[i] = false;
//     visited[s] = true;
//     queue<int> q;
//     q.push(s);
//     while(!q.empty()){
//         int current = q.front();
//         for(auto we : residual.edges[current]){
//             if(!visited[we.first] && we.second>0){
//                 visited[we.first] = true;
//                 q.push(we.first);
//             }
//             else if(!visited[we.first]){
//                 cut_capacity += graph.edges[current][we.first];
//             }
//         }
//         q.pop();
//     }
//     return cut_capacity;
// }

void FordFulkerson::PerformFordFulkerson(){
    bool visited[graph.numOfNodes+1];
    int predecessor[graph.numOfNodes+1];
    int capacity[graph.numOfNodes+1];
    while(BFS_Search(visited, predecessor, capacity, s, t)){
        flow += capacity[t];
        for (int current = t; current != s; current = predecessor[current]){
            auto it1 = residual.edges[predecessor[current]].find(current);
            auto it2 = residual.edges[current].find(predecessor[current]);
            it1->second -= capacity[t];
            it2->second += capacity[t];
        }
    }
    //FindCutCapacity();
    cut_capacity = 0;
    for(int i=1; i<=graph.numOfNodes; ++i){
        if(visited[i]){
            for (auto we: residual.edges[i]){
                if(!visited[we.first]){
                    cut_capacity += graph.edges[i][we.first];
                }
            }
        }
    }
}

int main(){
    int N, M;
    cin >> N >> M;
    Graph g(N+2);
    for(int j=1; j<=N; ++j){
        int unhappiness;
        cin >> unhappiness;
        g.addSingleEdge(j, N+2, unhappiness);
    }
    for(int i=1; i<=N; ++i){
        int unhappiness;
        cin >> unhappiness;
        g.addSingleEdge(N+1, i, unhappiness);
    }
    for(int k=0; k<M; ++k){
        int f1, f2, unhappiness;
        cin >> f1 >> f2 >> unhappiness;
        g.addDoubleEdge(f1, f2, unhappiness);
    }
    FordFulkerson ff(g, N+1, N+2);
    cout << ff.getCutCapacity();
}
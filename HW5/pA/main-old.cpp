#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cmath>
using namespace std;

//Declaring Functions, Structures, and Classes
    
    //Sets
int FindSetRootAndCollapse(int* arr, int i);
int FindSetRoot(int* arr, int i);
void Union(int* arr, int x, int y);
    
    //Edge
struct Edge{
    int EdgeID;
    int start, end, weight;
    Edge():EdgeID(0),start(0),end(0),weight(0){}
    Edge(int id, int s,int e,int w):EdgeID(id),start(s),end(e),weight(w){}
};
    
    //Binary Heap
class MaxBinaryHeap{
public:
    MaxBinaryHeap();
    MaxBinaryHeap(int n);
    bool isEmpty();
    void resetHeapSize(int n);

    //Max-Priority Queue
    void MaxHeapify(int node, int length);
    //void BuildMaxHeap(const std::vector<int>& array);
    void IncreaseKey(int edge_id, int newWeight);
    void MaxHeapInsert(int edge_id, int start, int end, int weight);
    Edge Maximum();
    Edge ExtractMax();
    std::vector<Edge> heap;
private:
    void swap(Edge& node1, Edge& node2);
    int FindPosition(int edge_id);
    int GetParent(int index);
};
    //Kruskal's Maximum Spanning Tree
    

int main(){
    int N;
    cin >> N;
    MaxBinaryHeap route;
    for(int i=1; i<N; ++i){
        int start, end, weight;
        cin >> start >> end >> weight;
        route.heap.push_back(Edge(i, start, end, weight));
    }
    int heapRealSize = route.heap.size()-1;
    for(int i=(route.heap.size()-1)/2; i>=1; --i){
        route.MaxHeapify(i, heapRealSize);
    }
    int DesiredStart, DesiredEnd;
    cin >> DesiredStart >> DesiredEnd;

    int VertexSet[N];
    vector<struct Edge> resultEdges;
    for(int i=0; i<N+1; ++i){
        VertexSet[i] = -1;
    }
    while(!route.isEmpty()){
        Edge theEdge = route.ExtractMax();
        if(FindSetRootAndCollapse(VertexSet, theEdge.start) != FindSetRootAndCollapse(VertexSet, theEdge.end)){
            resultEdges.push_back(theEdge);
            Union(VertexSet, theEdge.start, theEdge.end);
        }
    }
    struct WeightedEdge{
        int destination;
        int weight;
        WeightedEdge(int d, int w):destination(d),weight(w){}
    };
    list<struct WeightedEdge> AdjacencyList[N+1];
    for(auto x:resultEdges){
        AdjacencyList[x.start].push_back(WeightedEdge(x.end, x.weight));
        AdjacencyList[x.end].push_back(WeightedEdge(x.start, x.weight));
    }
    int minWeight[N+1];
    for(int i=0; i<=N; ++i) minWeight[i]=INT32_MAX;
    queue<int> bfsq;
    bfsq.push(DesiredStart);
    bool DesiredEndFound = false;
    while(!bfsq.empty()){
        if(DesiredEndFound) break;
        int u = bfsq.front();
        for(auto it = AdjacencyList[u].begin(); it!=AdjacencyList[u].end(); ++it){
            if((*it).destination!=DesiredEnd){
                minWeight[(*it).destination] = min(minWeight[u], (*it).weight);
                bfsq.push((*it).destination);
            }
            else{
                minWeight[(*it).destination] = min(minWeight[u], (*it).weight);
                cout << minWeight[DesiredEnd];
                DesiredEndFound = true;
                break;
            }
        }
        bfsq.pop();
    }

    return 0;
}


//Sets
int FindSetRootAndCollapse(int* arr, int i){
    int root;
    for(root=i; arr[root]>=0; root=arr[root]);

    //Collapse
    while(i != root){
        int parent = arr[i];
        arr[i] = root;
        i = parent;
    }

    return root;
}

int FindSetRoot(int* arr, int i){
    int root;
    for(root=i; root>=0; root=arr[root]);
    return root;
}

void Union(int* arr, int x, int y){
    int xroot = FindSetRootAndCollapse(arr,x);
    int yroot = FindSetRootAndCollapse(arr,y);
    
    bool larger = arr[xroot] < arr[yroot];
    if(larger){
        //y併進x
        arr[xroot] = arr[xroot] + arr[yroot];
        arr[yroot] = xroot;
    }
    else{
        //x併進y
        arr[yroot] = arr[xroot] + arr[yroot];
        arr[xroot] = yroot;
    }
}

//MaxBinaryHeap
MaxBinaryHeap::MaxBinaryHeap(){heap.resize(1);}
MaxBinaryHeap::MaxBinaryHeap(int n){heap.resize(n+1);}
bool MaxBinaryHeap::isEmpty(){return (heap.size()<=1);}
void MaxBinaryHeap::resetHeapSize(int n){heap.resize(n+1);}

//Max-Priority Queue
void MaxBinaryHeap::MaxHeapify(int node_index, int length){
    int left_index = node_index*2, right_index = left_index+1;
    int max = node_index;
    if(left_index<=length && heap[left_index].weight>heap[node_index].weight) max=left_index;
    if(right_index<=length && heap[right_index].weight>heap[max].weight) max = right_index;
    if(max != node_index){
        swap(heap[node_index], heap[max]);
        MaxHeapify(max, length);
    }
}
void MaxBinaryHeap::IncreaseKey(int edge_id, int newWeight){
    int index = FindPosition(edge_id);
    if(newWeight < heap[index].weight){
        std::cout << "New Key is smaller than before at node number " << edge_id << ", which is " << newWeight << ". Aborting..."; 
        return;
    }
    heap[index].weight = newWeight;
    int parentIndex = GetParent(index);
    while(parentIndex>0 && heap[index].weight>heap[parentIndex].weight){
        swap(heap[index], heap[parentIndex]);
        index = parentIndex;
        parentIndex = GetParent(index);
    }
}
void MaxBinaryHeap::MaxHeapInsert(int edge_id, int start, int end, int weight){
    heap.push_back(Edge(edge_id, start, end, weight));
    IncreaseKey(edge_id, weight);
}
Edge MaxBinaryHeap::Maximum(){ return heap[1];}
Edge MaxBinaryHeap::ExtractMax(){
    Edge retVal = heap[1];
    heap[1] = heap[heap.size()-1];
    heap.erase(heap.end()-1);
    MaxHeapify(1, int(heap.size()));
    return retVal;
}
void MaxBinaryHeap::swap(Edge& node1, Edge& node2){
    Edge temp = node1;
    node1 = node2;
    node2 = temp;
}
int MaxBinaryHeap::FindPosition(int edge_id){
    int index = 0;
    for(int i=1; i<heap.size(); ++i){
        if(heap.at(i).EdgeID==edge_id){
            index = i;
            break;
        }
    }
    return index;
}
int MaxBinaryHeap::GetParent(int index){ return index/2;}

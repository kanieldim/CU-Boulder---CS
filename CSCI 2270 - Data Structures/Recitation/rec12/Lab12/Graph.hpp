#include <iostream>
#include <vector>
using namespace std;


// Graph class represents a graph
// using adjacency list representation
class Graph 
{
    int n;    // No. of vertices
    vector <int> *adj;
    void dfs(int node, bool visited[]);
    bool isCyclicUtil(int v, bool visited[], bool recStack[]);

public:
    Graph(int n);

    void addEdge(int v1, int v2);

    // This function finds the vertex with max incoming edges
    int findMaxInDegree();

    // This function finds the no. of connected components in your undirected graph
    int findConnectedComponents();

    // This function tells if the graph is cyclic
    bool isCyclic();



};

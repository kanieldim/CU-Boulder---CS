/*

DISCLAIMER: This is a standard graph implementation we recommend everyone to at least have these functions implemented properly.

For the exams the variable type might change form int to char / any other custom type.
You will also have extra functions which will be the main exam problem which will be added to the hpp file and it will be given to you during your exam

*/


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

using namespace std;
struct vertex;


/*this is the struct for each vertex in the graph. */
struct vertex
{
    int id;
    vector<vertex*> Edges; //stores edges to adjacent vertices
};

class Graph
{
    public:
    /*
    class constructor
    Purpose: perform all operations necessary to instantiate a class object
    Parameters: none
    */
    Graph();

    /*
    class destructor
    Purpose: free all resources that the object has acquired
    Parameters: none
    */
    ~Graph();

    /*
    Method Name: addEdge
    Purpose: Creates an edge between two vertices (Add the pointer of vertex v2 to the vector of Edges in v1)
    Param: v1 - vertex at one end of edge
    Param: v2 - vertex at opposite end of edge
    */
    void addEdge(int v1, int v2);

    /*
    Method Name: addVertex
    Purpose: Creates a vertex

    Param: id - id of the vertex
    */
    void addVertex(int id);

    /*
    Method Name: displayEdges
    Purpose: print all edges in graph (see writeup for format)
    Parameters: none
    */
    void displayEdges();

    /*
    Method Name: printDFT
    Purpose: Iterate through the vertices, perform Depth first traversal by calling the
    DFTraversal function
    Parameters: none
    */
   void printDFT();

   /*
    Method Name: printBFT
    Purpose: Iterate through the vertices, perform Breadth first traversal by calling the
    DFTraversal function
    Parameters: none
    */
   void printBFT();

    /*
    Method Name: setAllVerticesUnvisited
    Purpose: Iterate through the vertices, mark them unvisited.
            This function is called prior to calling DFS after BFS
            has been performed so that the nodes can revisited again
            when DFS is called.
    Parameters: None
    */
    void setAllVerticesUnvisited();

  private:
    std::vector<vertex> vertices; //stores vertices

    /*
    Method Name: findVertex
    Purpose: Find and return the vertex of the specified id
    Param: id - id vertex to be returned
    returns pointer to a vertex
    */
    vertex *findVertex(int id);

    /*
    Method Name: BFTraversal
    Purpose: Call BFTraversal with a starting vertex and print the Breadth First Traversal from that vertex
    Param: v - pointer to the starting vertex for breadth first traversal
    */
    void BFTraversal(vertex *v);

    /*
    Method Name: DFTraversal
    Purpose: For starting vertex, print the Depth First Traversal from that vertex
    Param: v - pointer to the starting vertex for Depth first traversal
    */
    void DFTraversal(vertex *v);

};

#endif // GRAPH_HPP

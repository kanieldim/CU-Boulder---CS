#include <iostream>
#include "Graph.hpp"
using namespace std;


// Constructor
Graph::Graph(int n)
{
    this->n = n;
    adj = new vector<int>[n];
}

// function to add an edge to graph
void Graph::addEdge(int v1, int v2)
{
    adj[v1].push_back(v2);
}

void Graph::dfs(int node, bool visited[])
{
    // Mark each node as visted as and when we visit them
  visited[node] = true;

  for(int i = 0;i < adj[node].size(); i++)
  {
        if(visited[adj[node][i]] == false)
        {
          dfs(adj[node][i], visited);
        }
  }
}

// SILVER PROBLEM TODO : Complete the implementation of this function
// This function finds the vertex with max incoming edges
// Note: You can choose to do an efficient implementation using hashtable
int Graph::findMaxInDegree()
  {
    int max = 0;
    int max_vertex = 0;
    int count;

    for (int v = 0; v < n; v++){
      count = 0;
      for (int j = 0; j < n; j++)
      {
        for (int k = 0; k < adj[k].size(); k++)
        {
          if (adj[j][k] == v)
          {
            count++;
          }
        }
      }


      // TODO
      //Traverse through the adjacency list of all vertices to check how many times you encounter v
      //update the count accordingly

      //cout << count << endl;
      if (count > max)
        {
          max = count;
          max_vertex = v;
        }
    }

    return max_vertex;
  }

// GOLD PROBLEM TODO : Complete the implementation of this function
// This function finds the no. of connected components in your undirected graph

int Graph::findConnectedComponents()
{
    bool *visited = new bool[n];

    int connectedComponents = 0;
    //Initialize all nodes as not visited
    for(int i = 0; i < n; i++)
    {
      visited[i] = false;
    }

    // TODO

    return connectedComponents;
}



// Recursive helper function for isCyclic()
  bool Graph::isCyclicUtil(int v, bool visited[], bool recStack[])
  {

    if(visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // TODO Check for a cycle



    }


    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
  }

  // PLATINUM PROBLEM TODO: Complete the implementation of this function
  // Detect Cycles in a directed Graph

  bool Graph::isCyclic()
  {
    // Maintain a recursion stack (recStack[])
    // Mark all the vertices as not visited and not part of recursion stack

    bool *visited = new bool[n];
    bool *recStack = new bool[n];
    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    // TODO Call the recursive helper function on all connected components
    // and if there is cycle in any of it, return true


    return false;
  }

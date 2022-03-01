#include <iostream>
#include <string>
#include "Graph.hpp"

using namespace std;


Graph :: Graph()
{

}

Graph :: ~Graph()
{

}

void Graph :: addVertex(string cityName)
{
  vertex* newVertex = new vertex;
  newVertex -> name = cityName;
  newVertex -> visited = false;
  vertices.push_back(*newVertex);
}

void Graph :: addEdge(string city1, string city2, int distance)
{
  vertex *a = findVertex(city1);
  vertex *b = findVertex(city2);

  Edge *c = new Edge;
  c -> v = b;
  c -> distance = distance;
  a -> Edges.push_back(*c);
}

void Graph :: displayEdges()
{
  for (int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i].name << "-->";
    for (int j = 0; j < vertices[i].Edges.size(); j++)
    {
      cout << vertices[i].Edges[j].v -> name
      << " (" << vertices[i].Edges[j].distance << " miles)";
      if (j != vertices[i].Edges.size() - 1)
      {
        cout << "***";
      }
    }
    cout << endl;
  }
}

void Graph :: printDFT()
{
  setAllVerticesUnvisited();
  for (int i = 0; i < vertices.size(); i++)
  {
    string temp = vertices[i].name;
    vertex *temp1 = findVertex(temp);
    DFT_traversal(temp1);
  }
}

void Graph :: printBFT()
{
  setAllVerticesUnvisited();
  for (int i = 0; i < vertices.size(); i++)
  {
    string temp = vertices[i].name;
    vertex *temp1 = findVertex(temp);
    BFT_traversal(temp1);
  }
}
void Graph :: setAllVerticesUnvisited()
{
  for (int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
}

vertex* Graph :: findVertex(string name)
{
  vertex* fVertex = nullptr;
  for (unsigned i = 0; i < vertices.size(); i++)
  {
    if (vertices[i].name == name)
    {
      fVertex = &vertices[i];
      return fVertex;
    }
  }
  return fVertex;
}

void Graph :: BFT_traversal(vertex *v)
{
  vertex *tempName;
  queue<vertex*> queue;

  if (v -> visited == false)
  {
    queue.push(v);
  }

  while (!queue.empty())
  {
    tempName = queue.front();
    if (tempName -> visited == false)
    {
      tempName -> visited = true;
      cout << tempName -> name << endl;
    }

    for (int i = 0; i < tempName -> Edges.size(); i++)
    {
      if (tempName -> Edges[i].v -> visited == false)
      {
        cout << tempName -> Edges[i].v -> name << endl;
        tempName -> Edges[i].v -> visited = true;
        queue.push(tempName -> Edges[i].v);
      }
    }
    queue.pop();
  }
}

void Graph :: DFT_traversal(vertex *v)
{
  if (v -> visited == false)
  {
    cout << v -> name << endl;
    v -> visited = true;
  }
  for (int i = 0; i < v -> Edges.size(); i++)
  {
    if (v -> Edges[i].v -> visited == false)
    {
      DFT_traversal(v -> Edges[i].v);
    }
  }
}

#include <iostream>
#include "Graph.hpp"
using namespace std;

int main() {

	// SILVER PROBLEM
  cout<<"----------Create a directed graph with 7 vertices--------------------------"<<endl;

  Graph g1(7);
  g1.addEdge(0, 1);
  g1.addEdge(0, 2);
  g1.addEdge(1, 2);
  g1.addEdge(1, 6);
  g1.addEdge(1, 3);
  g1.addEdge(1, 4);
  g1.addEdge(3, 5);
  g1.addEdge(4, 5);
	g1.addEdge(6, 5);

  int max_indegree_vertex ;
	max_indegree_vertex = g1.findMaxInDegree();

	cout << "The vertex with most incoming edges is : "<<max_indegree_vertex<<endl;
	cout <<endl<<endl;



	// GOLD PROBLEM
  cout<<"----------Create an undirected graph with 6 vertices--------------------------"<<endl;

  Graph g2(6);
  g2.addEdge(0, 1);
  g2.addEdge(1, 0);

  g2.addEdge(1, 2);
  g2.addEdge(2, 1);

  g2.addEdge(0, 2);
  g2.addEdge(2, 0);

  g2.addEdge(3, 4);
  g2.addEdge(4, 3);


  int connectedComponents ;
	connectedComponents = g2.findConnectedComponents();

	cout << "Number of connected components: " << connectedComponents << endl;

  // PLATINUM PROBLEM
  cout<<"----------Create a directed graph with 7 vertices--------------------------"<<endl;

  Graph g3(7);
  g3.addEdge(0, 1);
  g3.addEdge(0, 2);
  g3.addEdge(1, 2);
  g3.addEdge(1, 6);
  g3.addEdge(1, 3);
  g3.addEdge(1, 4);
  g3.addEdge(3, 5);
  g3.addEdge(4, 5);
	g3.addEdge(6, 5);
  g3.addEdge(2, 0);

  bool is_graph_cyclic = false;
	is_graph_cyclic = g3.isCyclic();

  if(is_graph_cyclic)
    cout << "The graph is cyclic "<<endl;
  else
    cout << "The graph is not cyclic "<<endl;


}

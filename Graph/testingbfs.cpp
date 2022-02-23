#include <iostream>
#include "graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "Algorithms/bfs.h"


int main(){

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    //UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);
    graph -> insertVertex("E",35);

    graph -> createEdge("B","C",6);
    graph -> createEdge("E","C",8);
    graph -> createEdge("D","A",14);
    graph -> createEdge("B","A",1);
    graph -> createEdge("C","B",6);
    graph -> createEdge("D","C",8);
    graph -> createEdge("D","E",1);
    graph -> createEdge("A","E",1);
    graph -> createEdge("C","A",1);
    graph -> createEdge("D","B",1);
    graph -> createEdge("B","D",1);    
    graph -> display();

    BFS<int,int> bfs_alg(graph, "A");
    cout << "BFS: " << endl;
    bfs_alg.display();
    



}

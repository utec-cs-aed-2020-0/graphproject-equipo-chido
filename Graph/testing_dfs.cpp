#include <iostream>
#include "graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "Algorithms/dfs.h"


int main(){

    // DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);

    graph -> createEdge("A","B",10);
    graph -> createEdge("B","C",6);
    graph -> createEdge("C","D",8);
    graph -> createEdge("D","A",14);
    
    graph -> display();

    DFS<int,int> dfs_alg(graph, "A");
    dfs_alg.apply_search();
    cout << "DFS: " << endl;
    dfs_alg.display();
    



}
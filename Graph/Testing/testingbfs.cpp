#include <iostream>
#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/bfs.h"


int main(){

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    //UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);
    graph -> insertVertex("E",34);

    graph -> createEdge("A","B",10);
    graph -> createEdge("A","C",11);
    graph -> createEdge("B","E",14);
    graph -> createEdge("B","C",6);
    graph -> createEdge("C","D",8);
    graph -> createEdge("D","A",15);
    
    graph -> display();

    BFS<int,int> bfs_alg(graph, "A");
    cout << "BFS: " << endl;
    bfs_alg.display();
    



}

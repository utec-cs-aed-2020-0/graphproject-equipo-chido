#include <iostream>
#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/prim.h"


int main(){

    // DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("0",0);
    graph -> insertVertex("1",1);
    graph -> insertVertex("2",2);
    graph -> insertVertex("3",3);
    graph -> insertVertex("4",4);

    graph -> createEdge("0","1",1);
    graph -> createEdge("1","4",1);
    graph -> createEdge("4","3",1);
    graph -> createEdge("3","2",1);
    
    graph -> createEdge("2","0",6);
    graph -> createEdge("1","1",4);
    graph -> createEdge("1","3",3);

    graph -> display();

    Prim<int,int> prim_alg(graph);
    prim_alg.apply_search();
    // dfs_alg.apply_search();
    // cout << "DFS: " << endl;
    // dfs_alg.display();
    



}
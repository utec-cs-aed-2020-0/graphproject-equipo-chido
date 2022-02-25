#include <iostream>
#include "graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "Algorithms/greedybfs.h"


int main(){

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();

    graph -> insertVertex("S",12);
    graph -> insertVertex("A",9);
    graph -> insertVertex("B",8);
    graph -> insertVertex("C",7);
    graph -> insertVertex("D",6);
    graph -> insertVertex("E",0);
    graph -> insertVertex("F",4);
    graph -> insertVertex("G",3);
    graph -> insertVertex("H",7);
    graph -> insertVertex("I",9);
    graph -> insertVertex("J",9);
    graph -> insertVertex("K",4);
    graph -> insertVertex("L",6);

    graph -> createEdge("S","A", 1);
    graph -> createEdge("S","B", 2);
    graph -> createEdge("S","C", 3);
    graph -> createEdge("A","B", 4);
    graph -> createEdge("A","D", 5);
    graph -> createEdge("B","D", 6);
    graph -> createEdge("B","H", 7);
    graph -> createEdge("C","L", 8);
    graph -> createEdge("L","J", 9);
    graph -> createEdge("L","I", 10);
    graph -> createEdge("I","K", 11);
    graph -> createEdge("J","K", 12);
    graph -> createEdge("D","F", 13);
    graph -> createEdge("F","G", 14);
    graph -> createEdge("G","E", 15);
    graph -> createEdge("H","G", 16);
    graph -> createEdge("K","E", 17);

    graph -> display();
    Greedy<int,int> greedy_graph(graph,"S","E");
    greedy_graph.apply_search();
    cout << "Greedy BFS: " << endl;
    greedy_graph.display();
}
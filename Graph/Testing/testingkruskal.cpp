#include <iostream>
#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/kruskal.h"


int main(){

    UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);
    graph -> insertVertex("E",34);
    graph -> insertVertex("F",3);
    graph -> insertVertex("G",12);
    graph -> insertVertex("H",11);
    graph -> insertVertex("I",31);

    graph -> createEdge("A","B",4);
    graph -> createEdge("A","H",8);
    graph -> createEdge("B","H",11);
    graph -> createEdge("B","C",8);
    graph -> createEdge("C","D",7);
    graph -> createEdge("C","I",2);
    graph -> createEdge("C","F",4);
    graph -> createEdge("D","F",14);
    graph -> createEdge("D","E",9);
    graph -> createEdge("E","F",10);
    graph -> createEdge("F","G",2);
    graph -> createEdge("G","I",6); 
    graph -> createEdge("G","H",1);
    graph -> createEdge("H","I",7);  

    
    graph -> display();

    Kruskal<int,int> krus(graph);
    krus.apply();
    cout << "Kruskal: " << endl;
    krus.display();
}

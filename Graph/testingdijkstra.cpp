#include <iostream>
#include "graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "Algorithms/dijkstra.h"


int main(){

    UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);
    graph -> insertVertex("E",34);
    graph -> insertVertex("F",3);

    graph -> createEdge("A","B",1);
    graph -> createEdge("A","E",6);
    graph -> createEdge("A","C",3);
    graph -> createEdge("B","C",2);
    graph -> createEdge("B","D",3);
    graph -> createEdge("B","E",5);
    graph -> createEdge("C","D",5);
    graph -> createEdge("C","F",2);
    graph -> createEdge("D","E",2);
    graph -> createEdge("D","F",4);
    graph -> createEdge("F","E",1);

    
    graph -> display();

    Dijkstra<int,int> dijs(graph,"A");
    dijs.apply();
    cout << "Dijkstra1: " << endl;
    dijs.display();

    cout<<endl<<endl;

    DirectedGraph<int, int>* graph2 = new DirectedGraph<int, int>();

    graph2 -> insertVertex("A",30);
    graph2 -> insertVertex("B",50);
    graph2 -> insertVertex("C",25);
    graph2 -> insertVertex("D",35);
    graph2 -> insertVertex("E",34);
    graph2 -> insertVertex("F",3);

    graph2 -> createEdge("A","B",3);
    graph2 -> createEdge("A","D",6);
    graph2 -> createEdge("A","F",5);
    graph2 -> createEdge("B","C",1);
    graph2 -> createEdge("C","D",2);
    graph2 -> createEdge("E","F",2);
    graph2 -> createEdge("E","D",3);
    graph2 -> createEdge("B","F",1);
    graph2 -> createEdge("F","D",1);
    graph2 -> createEdge("D","B",3);

    
    graph2 -> display();

    Dijkstra<int,int> dijs2(graph2,"A");
    dijs2.apply();
    cout << "Dijkstra2: " << endl;
    dijs2.display();
}

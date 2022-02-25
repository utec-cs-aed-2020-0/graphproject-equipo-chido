#include <iostream>
#include "../graph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/bellman.h"


int main(){

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();

    graph -> insertVertex("A",5);
    graph -> insertVertex("B",6);
    graph -> insertVertex("C",2);
    graph -> insertVertex("D",8);
    graph -> insertVertex("E",4);

    graph -> createEdge("B","A",2);
    graph -> createEdge("B","C",2);
    graph -> createEdge("B","D",3);
    graph -> createEdge("C","A",-2);
    graph -> createEdge("D","E",-4);
    graph -> createEdge("E","C",1);
    
    graph -> display();

    Bellman<int,int> bell(graph,"B");
    bell.apply();
    cout << "Bellman Ford: " << endl;
    bell.display();
}
#include <iostream>
#include "graph.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"


int main(){ 

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    // UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();


    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);

    graph -> createEdge("A","B",10);
    graph -> createEdge("C","B",6);
    graph -> createEdge("D","A",8);
    graph -> createEdge("A","D",14);
    graph -> createEdge("B","D",5);
    graph -> createEdge("D","C",1);

    cout << "Inicio: " << endl;
    graph -> display();

    cout << "Peso entre A y B:" << graph -> operator()("A","B") << endl;
    graph -> deleteEdge("A", "B");
    cout << "1: " << endl;
    graph -> display();
    
    graph -> deleteVertex("A");
    cout << "2: " << endl;
    graph -> display();


    cout << "3: " << endl; 
    cout << "Densidad es : " << graph -> density() << endl;
    cout << "Densidad pasa threshold : " << graph -> isDense() << endl;
    cout << "El grafo está vació:" << graph -> empty() << endl;
    graph -> clear();
    cout << "El grafo está vació:" << graph -> empty() << endl;
    graph -> display();



    return 0; 
}
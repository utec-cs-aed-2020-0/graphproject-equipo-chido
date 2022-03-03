#include <iostream>
#include "../graph.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/astar.h"


int main(){

    // DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    // Ejemplo del ppt 36 de Búsqueda en Grafos (AED 2022-0)

    graph -> insertVertex("A",36);
    graph -> insertVertex("B",39);
    graph -> insertVertex("C",31);
    graph -> insertVertex("D",30);
    graph -> insertVertex("I",0);

    graph -> insertVertex("F",32);
    graph -> insertVertex("E",34);
    graph -> insertVertex("G",34);
    graph -> insertVertex("H",19);

    vector <int> heuristics;
    for (auto iter = graph -> vertexes.begin();iter != graph -> vertexes.end(); iter++){
        heuristics.push_back(iter -> second -> data);
    }

    graph -> createEdge("A","B", 22);
    graph -> createEdge("A","C", 9);
    graph -> createEdge("A","D", 12);
    graph -> createEdge("D","I", 30);

    graph -> createEdge("C","D", 4);
    graph -> createEdge("C","B", 35);


    graph -> createEdge("B","F", 36);
    graph -> createEdge("C","F", 42);

    graph -> createEdge("C","E", 65);
    graph -> createEdge("D","E", 33);
    graph -> createEdge("E","F", 18);


    graph -> createEdge("F","G", 39);
    graph -> createEdge("E","G", 23);
    graph -> createEdge("G","I", 21);


    graph -> createEdge("B","H", 34);
    graph -> createEdge("F","H", 24);
    graph -> createEdge("G","H", 25);
    graph -> createEdge("I","H", 19);

    graph -> display();
    AStar<int,int> astar_alg(graph,"A","I", heuristics);
    astar_alg.apply();
    astar_alg.display();
}
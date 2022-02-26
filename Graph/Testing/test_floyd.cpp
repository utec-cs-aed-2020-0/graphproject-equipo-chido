#include <iostream>
#include "../graph.h"
#include "../DirectedGraph.h"
#include "../Algorithms/floyd.h"


int main(){

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();

    graph -> insertVertex("1",1);
    graph -> insertVertex("2",1);
    graph -> insertVertex("3",1);
    graph -> insertVertex("4",1);
    graph -> insertVertex("5",1);
    

    graph -> createEdge("1","3",6);
    graph -> createEdge("1","4",3);

    graph -> createEdge("2","1",3);
    
    graph -> createEdge("3","4",2);

    graph -> createEdge("4","3",1);
    graph -> createEdge("4","2",1);

    graph -> createEdge("5","2",4);
    graph -> createEdge("5","4",2);

    graph -> display();

    Floyd<int,int> floyd(graph);
    floyd.apply();
    floyd.display();
    // cout << "Bellman Ford: " << endl;
    // bell.display();
};
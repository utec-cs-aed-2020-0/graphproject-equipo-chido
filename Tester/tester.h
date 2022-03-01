#ifndef TESTER_H
#define TESTER_H


#include <string>
#include <iostream>
#include <sstream>


#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Parser/parser.hpp"
#include "../Parser/helper_functs.hpp"
#include "../Graph/Algorithms/astar.h"
#include "../Graph/Algorithms/greedybfs.h"

#include "../Graph/Algorithms/bellman.h"

#include "../Graph/Algorithms/kruskal.h"



using namespace std;

struct Tester {
    static void executeExamples();
    static void executeParserPeru();
    //static void executeParserInternational();
};

void Tester::executeExamples() {
    cout << endl<< "---------------- GRAFOS BASICOS -----------------" << endl;

    DirectedGraph<int, int>* graph = new DirectedGraph<int, int>();
    // UnDirectedGraph<int, int>* graph = new UnDirectedGraph<int, int>();

    graph -> insertVertex("A",30);
    graph -> insertVertex("B",50);
    graph -> insertVertex("C",25);
    graph -> insertVertex("D",35);

    graph -> createEdge("A","B",10);
    graph -> createEdge("B","C",6);
    graph -> createEdge("C","D",8);
    graph -> createEdge("D","A",14);
    

    cout << "Inicio: " << endl;
    graph -> display();

    cout << "¿Está conectado?: " << graph -> isConnected() << endl;
    cout << "¿Está fuertemente conectado?: " << graph -> isStronglyConnected() << endl;
    graph -> createEdge("B","A",1);
    graph -> createEdge("C","B",6);
    graph -> createEdge("D","C",8);
    graph -> createEdge("A","D",1);
    graph -> createEdge("A","C",1);
    graph -> createEdge("C","A",1);
    graph -> createEdge("D","B",1);
    graph -> createEdge("B","D",1);
    cout << "¿Está fuertemente conectado?: " << graph -> isStronglyConnected() << endl;
    
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
    cout << "El grafo está vacio:" << graph -> empty() << endl;
    graph -> clear();
    cout << "El grafo está vacio:" << graph -> empty() << endl;
    graph -> display();

}

void Tester::executeParserPeru() {
    cout << endl<<"---------------- PARSER PERU -----------------" << endl;

    Parser Peru("Parser/Data/pe.json");
    Peru.readJSON();
    // Directed
    // DirectedGraph<string, double> uGraph;
    // DirectedGraph<string, double>* dir_graph = &uGraph; 
    // Peru.dGraphMake(uGraph);

    // UnDirectedGraph
    UnDirectedGraph<string, double> uGraph;
    UnDirectedGraph<string, double>* dir_graph = &uGraph; 
    Peru.uGraphMake(uGraph);
    cout<<endl;
    uGraph.display();


    string from = "Piura";
    string to = "Pucallpa";

    string to_dists = uGraph.vertexes[to]->data;
    string lat_2 = to_dists.substr(0,to_dists.find("\n"));
    string lon_2 = to_dists.substr(to_dists.find("\n")+1,to_dists.size());


    vector<double> heuristic;
    for (auto iter = uGraph.vertexes.begin(); iter != uGraph.vertexes.end(); iter++){
        // cout << "Ciudad: " << iter -> first << " -> Coordenadas: \n" << iter -> second -> data << endl; 
        string dists = iter -> second -> data;
        string lat_1 = dists.substr(0,dists.find("\n"));
        string lon_1 = dists.substr(dists.find("\n")+1,dists.size());
        double value = distance(lat_1, lon_1, lat_2, lon_2);
        heuristic.push_back(value);
    }
    // Create heuristics

    /*  A-Star Implementación 
    cout << "El mejor camino para ir de " << from << " a " << to  << " es : " << endl; 
    AStar<string,double> astar_alg(dir_graph,from,to, heuristic);
    astar_alg.apply();
    astar_alg.display(); */

    /* GREEDY DFS IMPLEMENTACIÓN
    Greedy<string,double> greedy_alg(dir_graph,from,to, heuristic);
    greedy_alg.apply();
    greedy_alg.display(); */

    /* BELLMAN IMPLEMENTACIÓN
    Bellman<string,double> bell(dir_graph,"Cuzco    ");
    bell.apply();
    cout << "Bellman Ford: " << endl;
    bell.display();  */ 

    /* Kruskal Implementación
    Kruskal<string,double> krus(dir_graph);
    krus.apply();
    UnDirectedGraph<string, double>* graph2 = krus.kruskal_(krus);
    cout << "\nKruskal Implementación: " << endl;
    graph2->display();  */
}

/*
void Tester::executeParserInternational() {
    cout << endl<<"---------------- PARSER INTERNACIONAL -----------------" << endl;
    Parser graph("Parser/Data/airports.json");
    graph.readJSON();
    DirectedGraph<string, double> dGraph;
    graph.dGraphMake(dGraph);
    dGraph.display();
}
*/

#endif
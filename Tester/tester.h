#ifndef TESTER_H
#define TESTER_H

#include "../Graph/DirectedGraph.h"
#include "../Graph/UndirectedGraph.h"
#include "../Parser/parser.hpp"
#include <string>
#include <iostream>

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
    DirectedGraph<string, double> uGraph;

    Peru.dGraphMake(uGraph);
    cout<<endl;
    uGraph.display();
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
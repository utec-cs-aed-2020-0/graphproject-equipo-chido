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
#include "../Graph/Algorithms/prim.h"

#include "../Graph/Algorithms/dijkstra.h"

#include "../Graph/Algorithms/floyd.h"

using namespace std;

struct Tester {
    static void executeExamples();
    static void executeParserPeru();
    static void excecuteDirected(Parser Peru);
    static void excecuteUnDirected(Parser Peru);
    static void executeParserInternational();
    static vector<double> create_heuristics(Graph<string, double>* grafo,string to);
    static void astar_test(Graph<string,double>* dir_graph, string from, string to, vector<double> heuristic);
    static void floyd_test(Graph<string,double>* dir_graph);
    static void greedydfs_test(Graph<string,double>* dir_graph, string from, string to, vector<double> heuristic);
    static void dijkstra_test(Graph<string,double>* dir_graph, string from);
    static void bellman_test(DirectedGraph<string,double>* dir_graph, string from);
    static void kruskal_test(UnDirectedGraph<string,double>* dir_graph);
    static void prim_test(UnDirectedGraph<string,double>* dir_graph);
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

    string grafo_tipo ="u";
    cout << "¿Desea que el Grafo sea dirigido (d) o no dirigido (u) ? Escriba (d) o (u)" << endl;
    cin >> grafo_tipo;

    cout << grafo_tipo;
    if (grafo_tipo == "u"){
        excecuteUnDirected(Peru);
    } 
    else if (grafo_tipo == "d"){
        excecuteDirected(Peru);
    }

}

void Tester::excecuteDirected(Parser Peru){
    cout << "hoasdas " << endl; 
    DirectedGraph<string, double> nGraph;
    DirectedGraph<string, double>* dir_graph = &nGraph; 
    Peru.dGraphMake(nGraph);
    nGraph.display();

    string operacion;
    do{
        cout << "\n¿Qué tipo de operación desea aplicar?\n" << 
        " 1. A-Star\n" <<
        " 2. Floyd-Warshall\n" <<
        " 3. Greedy BFS\n" <<
        " 4. Dijkstra\n" <<
        " 5. Bellman\n" << endl;
        cin >> operacion;

        if (operacion == "1"){ // A-Star
            string to;
            string from;
            cout << "Indica el lugar de procedencia del viaje: "; 
            cin >> from; 

            cout << "Indica el lugar de destino del viaje: "; 
            cin >> to;
 
            vector<double> heuristica = create_heuristics(dir_graph,to);
            astar_test(dir_graph,from,to,heuristica);
            system("pause");
        }
        else if (operacion == "2"){ // Floyd-Warshall
            floyd_test(dir_graph);
            system("pause");
        }
        else if (operacion == "3"){ // Greedy BFS
            string to;
            string from;
            cout << "Indica el lugar de procedencia del viaje: "; 
            cin >> from; 

            cout << "Indica el lugar de destino del viaje: "; 
            cin >> to;
 
            vector<double> heuristica = create_heuristics(dir_graph,to);
            greedydfs_test(dir_graph,from,to,heuristica);
            system("pause");

        }
        else if (operacion == "4"){ // Dijkstra
            string from;
            cout << "Indica el lugar de procedencia del viaje del cual desea explorar todas las opciones de vuelo:";
            cin >> from;
            dijkstra_test(dir_graph,from);
            system("pause");
        }
        else if (operacion == "5"){ // Bellman
            string from;
            cout << "Indica el lugar de procedencia del viaje del cual desea explorar todas las opciones de vuelo:";
            cin >> from;
            bellman_test(dir_graph,from);
            system("pause");
        }
        else
            operacion = "0";

    }while(operacion != "0");
}

void Tester::excecuteUnDirected(Parser Peru){

    UnDirectedGraph<string, double> nGraph;
    UnDirectedGraph<string, double>* dir_graph = &nGraph; 
    Peru.uGraphMake(nGraph);
    nGraph.display();

    string operacion;
    do{
        cout << "\n¿Qué tipo de operación desea aplicar?\n" << 
        " 1. A-Star\n" <<
        " 2. Floyd-Warshall\n" <<
        " 3. Greedy BFS\n" <<
        " 4. Dijkstra\n" <<
        " 5. Kruskal\n" <<
        " 6. Prim\n" << endl;
        cin >> operacion;

        if (operacion == "1"){ // A-Star
            string to;
            string from;
            cout << "Indica el lugar de procedencia del viaje: "; 
            cin >> from; 

            cout << "Indica el lugar de destino del viaje: "; 
            cin >> to;
 
            vector<double> heuristica = create_heuristics(dir_graph,to);
            astar_test(dir_graph,from,to,heuristica);
            system("pause");
        }
        else if (operacion == "2"){ // Floyd-Warshall
            floyd_test(dir_graph);
            system("pause");
        }
        else if (operacion == "3"){ // Greedy BFS
            string to;
            string from;
            cout << "Indica el lugar de procedencia del viaje: "; 
            cin >> from; 

            cout << "Indica el lugar de destino del viaje: "; 
            cin >> to;
 
            vector<double> heuristica = create_heuristics(dir_graph,to);
            greedydfs_test(dir_graph,from,to,heuristica);
            system("pause");

        }
        else if (operacion == "4"){ // Dijkstra
            string from;
            cout << "Indica el lugar de procedencia del viaje del cual desea explorar todas las opciones de vuelo:";
            cin >> from;
            dijkstra_test(dir_graph,from);
            system("pause");
        }
        else if (operacion == "5"){ // Kruskal
            kruskal_test(dir_graph);
            system("pause");
        }
        else if(operacion == "6"){ // PRIM
            prim_test(dir_graph);
            system("pause");
        }
        else
            operacion = "0";

    }while(operacion != "0");     
}

void Tester::executeParserInternational() {
    cout << endl<<"---------------- PARSER INTERNACIONAL -----------------" << endl;
    Parser graph("Parser/Data/airports.json");
    graph.readJSON();
    DirectedGraph<string, double> dGraph;
    graph.dGraphMake(dGraph);
    dGraph.display();
}

vector<double> Tester::create_heuristics(Graph<string, double>* dir_grafo,string to){
    
    string to_dists = dir_grafo -> vertexes[to]->data;
    string lat_2 = to_dists.substr(0,to_dists.find("\n"));
    string lon_2 = to_dists.substr(to_dists.find("\n")+1,to_dists.size());

    vector<double> heuristic;
    for (auto iter = dir_grafo -> vertexes.begin(); iter != dir_grafo -> vertexes.end(); iter++){
        // cout << "Ciudad: " << iter -> first << " -> Coordenadas: \n" << iter -> second -> data << endl; 
        string dists = iter -> second -> data;
        string lat_1 = dists.substr(0,dists.find("\n"));
        string lon_1 = dists.substr(dists.find("\n")+1,dists.size());
        double value = distance(lat_1, lon_1, lat_2, lon_2);
        heuristic.push_back(value);
    } 

    return heuristic;
}

void Tester::astar_test(Graph<string,double>* dir_graph, string from, string to, vector<double> heuristic){
    AStar<string,double> astar_alg(dir_graph,from,to, heuristic);
    astar_alg.apply();
    astar_alg.display();
}

void Tester::floyd_test(Graph<string,double>* dir_graph){
    
    Floyd<string,double> floyd(dir_graph);
    floyd.apply();
    floyd.display();
    
    string from,to;
    string option;
    
    do{
        cout << "¿Desea conocer el camino más rápido entre dos aeropuertos?: (s) Sí (n) No " << endl;
        cin >> option;

        if (option == "s"){
            cout << "Indica el lugar de procedencia del viaje: "; 
            cin >> from; 

            cout << "Indica el lugar de destino del viaje: "; 
            cin >> to;
        
            floyd.show_path(from,to);
        }
        else{
            break;
        }

    }
    while(true);
}

void Tester::greedydfs_test(Graph<string,double>* dir_graph, string from, string to, vector<double> heuristic){
    Greedy<string,double> greedy_alg(dir_graph,from,to, heuristic);
    greedy_alg.apply();
    greedy_alg.display(); 
}

void Tester::dijkstra_test(Graph<string,double>* dir_graph, string from){
    Dijkstra<string,double> dijs(dir_graph,from);
    dijs.apply();
    dijs.display(); 
};

void Tester::bellman_test(DirectedGraph<string,double>* dir_graph, string from){
    Bellman<string,double> bell(dir_graph,from);
    bell.apply();
    bell.display();
}

void Tester::kruskal_test(UnDirectedGraph<string,double>* dir_graph){
    Kruskal<string,double> krus(dir_graph);
    krus.apply();
    UnDirectedGraph<string, double>* graph2 = krus.kruskal_(krus);
    graph2->display(); 
};

void Tester::prim_test(UnDirectedGraph<string,double>* dir_graph){
    Prim<string,double> prim_alg(dir_graph);
    UnDirectedGraph<string, double> prim_result = prim_alg.apply(); 
    prim_alg.display();
};



#endif
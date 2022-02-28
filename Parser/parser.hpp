#ifndef PARSER_HPP
#define PARSER_HPP

#include "nlohmann/json.hpp"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"
#include "helper_functs.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <tuple>   
using namespace std;

using json = nlohmann::json;

class Parser
{
private:
    string path;                
    json jsonGraph;             // almacena el json que va a ser accedido mas adelante
public:
    Parser(string path_);

    void clear();

    void readJSON();

    void uGraphMake(UnDirectedGraph<string, double> &tempGraph);

    void dGraphMake(DirectedGraph<string, double> &tempGraph);
};

Parser::Parser(string path_) {
    this->path = path_;
}

void Parser::clear() {
    this->path = "";
    this->jsonGraph.clear();
}

void Parser::readJSON() {
    ifstream file(this->path, ifstream::in);        // se abre el json en modo lectura
    string line, jsonString;
    while (getline(file, line))                     // se lee el json a una std::string
        jsonString += line + "\n";
    this->jsonGraph = json::parse(jsonString);            // se parsea a un objeto nlohmann::json
    //cout << setw(4) << this->jsonGraph << endl;         // imprime el json
}

void Parser::uGraphMake(UnDirectedGraph<string, double> &tempGraph) {
    //tuple<json,json> aux;
    for (int i = 0; i < this->jsonGraph.size(); i++){
        string aux = this->jsonGraph[i]["Latitude"];
        aux += '\n';
        aux += this->jsonGraph[i]["Longitude"];
        tempGraph.insertVertex(this->jsonGraph[i]["City"], aux);}   // se crean los vértices
    
    for (int i = 0; i < this->jsonGraph.size(); i++) {   // se crean los edges
        for (int j = 0; j < this->jsonGraph[i]["destinations"].size(); j++) {
            //cout<<"uniendo: "<<this->jsonGraph[i]["City"]<<" con "<<this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["City"]<<endl;
            tempGraph.createEdge(this->jsonGraph[i]["City"], // con la primera ciudad, la segunda ciudad y la distancia euclidiana entre ellas
                                this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["City"],
                                distance(this->jsonGraph[i]["Latitude"],
                                        this->jsonGraph[i]["Longitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Latitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Longitude"]
                                    )
                                );   
        }
    }
}

void Parser::dGraphMake(DirectedGraph<string, double> &tempGraph) {
    for (int i = 0; i < this->jsonGraph.size(); i++){
        string aux = this->jsonGraph[i]["Latitude"];
        aux += '\n';
        aux += this->jsonGraph[i]["Longitude"];
        tempGraph.insertVertex(this->jsonGraph[i]["City"], aux);}   // se crean los vértices
    
    for (int i = 0; i < this->jsonGraph.size(); i++) {   // se crean los edges
        for (int j = 0; j < this->jsonGraph[i]["destinations"].size(); j++) {
            //cout<<"uniendo: "<<this->jsonGraph[i]["City"]<<" con "<<this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["City"]<<endl;
            tempGraph.createEdge(this->jsonGraph[i]["City"], // con la primera ciudad, la segunda ciudad y la distancia euclidiana entre ellas
                                this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["City"],
                                distance(this->jsonGraph[i]["Latitude"],
                                        this->jsonGraph[i]["Longitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Latitude"],
                                        this->jsonGraph[findByAirportID(this->jsonGraph, this->jsonGraph[i]["destinations"][j])]["Longitude"]
                                    )
                                );   
        }
    }
}



#endif // PARSER_HPP

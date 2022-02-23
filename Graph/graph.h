#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV,TE>* vertexes[2];
    TE weight;

    Edge(){
      this->vertexes[0]=nullptr;
      this->vertexes[1]=nullptr;
      this->weight=0;
    }
    Edge(Vertex<TV,TE>* Start, Vertex<TV,TE>* End,TE peso){
      this->vertexes[0]=Start;
      this->vertexes[1]=End;
      this->weight=peso;
    }

};

template<typename TV, typename TE>
struct Vertex {
    string id;  
    TV data;
    std::list<Edge<TV, TE>*> edges;

    Vertex(){
      this->data=0;
    };
    Vertex(TV dato, string id){
      this -> data=dato;
      this -> id = id; 
    }
};

template<typename TV, typename TE>
class Graph{

public:
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    virtual bool insertVertex(string id, TV vertex) = 0;   
    virtual bool createEdge(string id1, string id2, TE w) = 0;     
    virtual bool deleteVertex(string id) = 0;     
    virtual bool deleteEdge(string id_inicio, string id_final) = 0;   
    virtual TE &operator()(string start, string end)= 0;  
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected()= 0;
    virtual bool isStronglyConnected() = 0;
    virtual bool empty() = 0;
    virtual void clear()= 0;  
    virtual void displayVertex(string id)= 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;
};

#endif

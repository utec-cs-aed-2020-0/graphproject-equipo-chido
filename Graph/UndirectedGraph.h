#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    UnDirectedGraph(){};
    ~UnDirectedGraph() = default;

    bool insertVertex(string id, TV vertex){throw("missing");}

    bool createEdge(string id1, string id2, TE w){
        // Si existen los vertices agrega la arista en ambos
        if (findById(id1) && findById(id2)) {
            Edge<TV, TE>* edgecreado = new Edge<TV, TE>(this->vertexes[id1],this->vertexes[id2],w));
            this->vertexes[id1]->edges.push_back(edgecreado);
            this->vertexes[id2]->edges.push_back(edgecreado);
            return true;
        }
        return false;
    }

    bool deleteVertex(string id){
        if (findById(id)){
            //Si existe el vertice elimina las aristas que esten conectadas
            for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
                if (it->first != id)
                    deleteEdge(it->first, id);
            }
            this->vertexes.erase(this->vertexes.find(id));
            return true;
        }
        return false;
    }

    bool deleteEdge(string id){throw("missing");}

    TE &operator()(string start, string end){
        if (findById(start) && findById(end)) {
            //Si existen los vertices start y end
            for (auto edge : this->vertexes[start]->edges) {
                //Se busca la arista que los una y retorna el peso
                if (edge->vertexes[0] == this->vertexes[start] && edge->vertexes[1] == this->vertexes[end])
                    return edge->weight;
            }
        }
        throw("no existe");
    }

    float density(){
        float v, e;
        //contar vertices y aristas
        v = this->vertexes.size();
        e = 0;
        for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
            e += it->second->edges.size();
        }
        e = e/2; //eliminar la redundancia (por probar*)

        //formula para un grafo no dirigido
        return 2*e/(v*(v-1));
    }

    bool isDense(float threshold = 0.5){throw("missing");}

    bool isConnected(){throw("missing");}
    
    //solo aplica para grafos dirigidos
    bool isStronglyConnected() throw(){};

    bool empty(){
        return (this->vertexes.size()==0;)
    }

    void clear(){
        this->vertexes.clear();
    }
      
    void displayVertex(string id){throw("missing");}

    bool findById(string id){
        return (this->vertexes.find(id) != this->vertexes.end());
    }

    void display(){throw("missing");}

};

#endif
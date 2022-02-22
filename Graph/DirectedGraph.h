#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{

    public:
        DirectedGraph(){};
        ~DirectedGraph() = default;

        bool insertVertex(string id, TV vertex){ // Listo - Validado
            Vertex<TV,TE>* vertexcreado = new Vertex<TV,TE>(vertex,id);
            this -> vertexes[id] = vertexcreado;
            return true;
        }

        bool createEdge(string id1, string id2, TE w){ // Listo - Validado
            // Si existen los vertices agrega la arista
            if (findById(id1) && findById(id2)) {
                Edge<TV, TE>* edgecreado = new Edge<TV, TE>(this->vertexes[id1],this->vertexes[id2],w);
                this->vertexes[id1]->edges.push_back(edgecreado);
                return true;
            }
            return false;
        }

        bool deleteVertex(string id){ // Listo - Validado
            if (findById(id)){
                //Si existe el vertice elimina las aristas que apunten a este
                for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
                    if (it->first != id)
                        deleteEdge(it->first, id);
                }
                this->vertexes.erase(this->vertexes.find(id));
                return true;
            }
            return false;
        }

        bool deleteEdge(string id_inicio, string id_final){ // Listo - Validado
            if (findById(id_inicio) && findById(id_final)){
                // Borrar los edges de id_inicio -> id_final
                auto iter_dir = this->vertexes.find(id_inicio);
                Vertex<TV,TE>* vert1 = iter_dir -> second;
                for (auto edge : vert1 -> edges){ // Recorrer los edges
                    if ( (edge -> vertexes[0] == this -> vertexes[id_inicio]) && (edge -> vertexes[1] == this -> vertexes[id_final]) )
                    {
                        vert1 -> edges.remove(edge);
                        return true;
                    }
                }

            }
            return false;
        }

        TE &operator()(string start, string end){ // Listo - Validado
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

        float density(){ // Listo - Validado
            float v, e;
            //contar vertices y aristas
            v = this->vertexes.size();
            e = 0;
            for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
                e += it->second->edges.size();
            }
            //formula para un grafo dirigido
            return e/(v*(v-1));
        }

        bool isDense(float threshold = 0.5){ // Listo - Validado
        return (density() >= threshold) ? true : false;   
        }

        bool isConnected(){throw("missing");}

        bool isStronglyConnected(){throw("missing");}

        bool empty(){ // Listo - Validado
            return (this->vertexes.size()==0) ? true : false;
        }

        void clear(){ // Listo - Validado
            this->vertexes.clear();
        }
        
        void displayVertex(string id){ // Listo - Validado
            if (findById(id)){
                auto iter = this->vertexes.find(id);
                cout<< "Vértice: " << iter -> first;
                Vertex<TV,TE>* vert = iter -> second;

                cout << " -> "; 
                for (auto edge : vert -> edges){
                        cout << " (hacia " << edge -> vertexes[1] -> id << " - Peso: " <<edge -> weight <<  ")";
                }

                cout << endl;
                return; 
            }
            throw ("Missing");
        }

        bool findById(string id){ // Listo - Validado
            return (this->vertexes.find(id) != this->vertexes.end());
        }

        void display(){ // Listo - Validado
            for (auto iter = this -> vertexes.begin(); iter != this -> vertexes.end(); iter++){
                displayVertex(iter -> first);
            }
        }

};

#endif
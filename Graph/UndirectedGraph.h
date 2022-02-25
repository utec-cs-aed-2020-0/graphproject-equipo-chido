#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <list>

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{

    public: 

        UnDirectedGraph(){};
        ~UnDirectedGraph() = default;

        bool insertVertex(string id, TV vertex){ // Listo - Validado
            Vertex<TV,TE>* vertexcreado = new Vertex<TV,TE>(vertex,id);
            this -> vertexes[id] = vertexcreado;
            return true;
        }

        bool createEdge(string id1, string id2, TE w){ // Listo- Validado
            // Si existen los vertices agrega la arista en ambos
            if (findById(id1) && findById(id2)) {
                Edge<TV, TE>* edgecreado = new Edge<TV, TE>(this->vertexes[id1],this->vertexes[id2],w);
                this->vertexes[id1]->edges.push_back(edgecreado);
                this->vertexes[id2]->edges.push_back(edgecreado);
                return true;
            }
            return false;
        }

        bool deleteVertex(string id){ // Listo - Validado
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

        bool deleteEdge(string id_inicio, string id_final){ // Listo - Validado

            if (findById(id_inicio) && findById(id_final)){
                // Borrar los edges de id_inicio -> id_final
                auto iter_dir = this->vertexes.find(id_inicio);
                Vertex<TV,TE>* vert1 = iter_dir -> second;
                for (auto edge : vert1 -> edges){ // Recorrer los edges
                    if ((edge -> vertexes[0] == this -> vertexes[id_inicio]) && (edge -> vertexes[1] == this -> vertexes[id_final]) || (edge -> vertexes[1] == this -> vertexes[id_inicio]) && (edge -> vertexes[0] == this -> vertexes[id_final]) )
                    {
                        vert1 -> edges.remove(edge);
                        break;
                    }
                }
                // Borrar los edges de id_final -> id_inicio
                iter_dir = this -> vertexes.find(id_final);
                vert1 = iter_dir -> second;
                for (auto edge : vert1 -> edges){ // Recorrer los edges
                    if ((edge -> vertexes[0] == this -> vertexes[id_inicio]) && (edge -> vertexes[1] == this -> vertexes[id_final]) || (edge -> vertexes[1] == this -> vertexes[id_inicio]) && (edge -> vertexes[0] == this -> vertexes[id_final]) )
                    {
                        vert1 -> edges.remove(edge);
                        break;
                    }
                }
                return true;
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
            e = e/2; //eliminar la redundancia (por probar*)
            //formula para un grafo no dirigido
            return 2*e/(v*(v-1));
        }

        bool isDense(float threshold = 0.5){ // Listo - Validado
            return (density() >= threshold) ? true : false;   
        }

        bool isConnected(){ // Listo - Validado
            // Crear dos array uno para string y a partir del id, darle el valor al visited[i]
            std::unordered_map<string, bool> visited_table;

            // Reinicializar el nodo puntero (inicial - u)
            auto iter =  this -> vertexes.begin();
            for (iter = this -> vertexes.begin(); iter != this -> vertexes.end(); iter++){
                visited_table[iter -> first] = false;
            }

            iter =  this -> vertexes.begin();
            Vertex<TV,TE>* vertex_u = iter -> second;
            std::list<string> stack; // Stack de verificación

            // Inicializar
            visited_table[vertex_u -> id] = true;
            stack.push_back(vertex_u -> id);
            bool found_new = false;

            while (!stack.empty()){
                for (auto edge : vertex_u -> edges){
                    string edge_other;
                    if (edge -> vertexes[1] -> id != vertex_u -> id)
                        edge_other = edge -> vertexes[1] -> id;
                    else 
                        edge_other = edge -> vertexes[0] -> id;
                    
                    if (visited_table[edge_other] == false){
                        stack.push_back(edge_other);
                        visited_table[edge_other] = true;
                        vertex_u = this -> vertexes[edge_other];
                        found_new = true;
                        break;
                    }
                }
                if (!found_new){
                        stack.pop_back(); 
                        if (!stack.empty())
                            vertex_u = this -> vertexes[stack.back()];
                }
                found_new = false;
            }

            bool isConnected_val = true;

            for (auto iter = visited_table.begin(); iter != visited_table.end(); iter++){
                isConnected_val = isConnected_val & iter -> second;
            }


            return isConnected_val;

        };
        bool isStronglyConnected(){throw("Error");}; //solo aplica para grafos dirigidos

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
                    if (edge -> vertexes[0] != vert)
                        cout << " " << edge -> vertexes[0] -> id << " (" << edge ->  weight <<  ")";
                    else if (edge -> vertexes[1] != vert)
                        cout << " " << edge -> vertexes[1] -> id << " (" << edge -> weight <<  ")";
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

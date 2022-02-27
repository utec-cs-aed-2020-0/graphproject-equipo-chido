#ifndef DFS_H
#define DFS_H

#include "../graph.h"
#include <iostream>
template<typename TV, typename TE>

class DFS{
    
    private:
        Graph<TV,TE>* graph;
        std::unordered_map<string, bool> visited_table;
        std::list<string> stack; // Stack de verificación
        string id_inicial;
        UnDirectedGraph<TV,TE>* DFS_graph = new UnDirectedGraph<TV,TE>() ;


    public:
        DFS(Graph<TV,TE>* _graph, string _id_inicial) : graph(_graph), id_inicial(_id_inicial) {

            // Inicializar la tabla visitada
            auto iter =  graph -> vertexes.begin();

            for (iter = graph -> vertexes.begin(); iter != graph -> vertexes.end(); iter++){
                visited_table[iter -> first] = false;
            }

        }; 
        ~DFS() = default;

        void apply_search(){

            // Reinicializar el nodo puntero (inicial - u)
            auto iter =  graph -> vertexes.find(this-> id_inicial);
            Vertex<TV,TE>* vertex_u = iter -> second;

            // Inicializar grafo
            DFS_graph -> insertVertex(vertex_u -> id, vertex_u ->data);

            // Inicializa variables
            visited_table[vertex_u -> id] = true;
            stack.push_back(vertex_u -> id);
            bool found_new = false;

            while (!stack.empty()){
                for (auto edge : vertex_u -> edges){
                    string  edge_other = (edge -> vertexes[1] -> id != vertex_u -> id) ?
                         edge -> vertexes[1] -> id : edge -> vertexes[0] -> id;
                    
                    if (visited_table[edge_other] == false){
                        // Pushear a Stack e identificar como visitado
                        stack.push_back(edge_other);
                        visited_table[edge_other] = true;

                        // Creación de Árbol
                        DFS_graph -> insertVertex(edge_other, graph -> vertexes[edge_other] -> data);
                        DFS_graph -> createEdge(vertex_u -> id, edge_other,edge -> weight);

                        // Reemplazar y validar
                        vertex_u = graph -> vertexes[edge_other];
                        found_new = true;
                        break;
                    }
                }

                if (!found_new){
                        stack.pop_back(); 
                        if (!stack.empty())
                            vertex_u = graph -> vertexes[stack.back()];
                }
                found_new = false;
            }

        };
        Graph<TV,TE>* get_graph(){return DFS_graph;}

        void display(){
            DFS_graph -> display();
        }



};




#endif
#ifndef PRIM_H
#define PRIM_H

#include <iostream>
#include <queue>
#include <limits>

template<typename TV, typename TE>
class Prim{
    private:

        // Argumentos de entrada y salida
        UnDirectedGraph<TV,TE>* graph;
        UnDirectedGraph<TV,TE> Prim_BST;

        // Atributos útiles
        std::unordered_map<string,TE> table_weights; // Lista de todas las aristas inicidas con Infinito   
        std::unordered_map<string,string> padres;



        string extraerMinimo(){
            int val = std::numeric_limits<int>::max();
            string id_min;
            for (auto iter_n = table_weights.begin(); iter_n != table_weights.end(); iter_n++){
                if (iter_n -> second < val){
                    id_min = iter_n -> first;
                    val = iter_n -> second;
                }
            }

            return id_min;
        }

    public:
        Prim(UnDirectedGraph<TV,TE>* _graph) : graph(_graph){}; 
        ~Prim() = default;

        UnDirectedGraph<TV,TE> apply(){ 
            // Inicializar la cola de los pares de vértices
            for (auto iter = graph -> vertexes.begin(); iter != graph -> vertexes.end();iter++){
                table_weights[iter->first] = std::numeric_limits<int>::max();
            }

            // Primer valor a evaluar de la cola 
            Vertex<TV,TE>* vert = graph -> vertexes.begin() -> second;
            table_weights[vert->id] = 0;
            padres[vert -> id] = "-";
            Prim_BST.insertVertex(vert-> id,  vert -> data);

            while(!table_weights.empty()){
                // Devuelve el mínimo y lo extrae de la cola
                string vert_eval = extraerMinimo();
                table_weights.erase(vert_eval);
                
                
                for (auto edge : graph -> vertexes[vert_eval] -> edges){ // Evaluar los vértices hacia los que va el vértice 
                    string  id_neigh = (edge -> vertexes[1] -> id != vert_eval) ?
                         edge -> vertexes[1] -> id : edge -> vertexes[0] -> id;

                    TE peso = edge -> weight;

                    if (table_weights.find(id_neigh) != table_weights.end()){
                        if (table_weights[id_neigh] > peso){
                            Prim_BST.insertVertex(id_neigh, graph -> vertexes[id_neigh] -> data);
                            Prim_BST.createEdge(vert_eval, id_neigh, peso);
                            table_weights[id_neigh] = peso;
                            padres[id_neigh] = vert_eval;
                        }
                    }
                }
            }

            for (auto iter = padres.begin(); iter != padres.end();iter++){
                cout << "El nodo " << iter -> first << " tiene como padre: " << iter -> second<< endl;
            }

            return Prim_BST;
        };


        void display(){ 
            // Mostrar BST
            for (auto iter = padres.begin(); iter != padres.end();iter++){
                cout << "El nodo " << iter -> first << " tiene como padre: " << iter -> second<< endl;
            }
        }       

        


};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> clau-dev

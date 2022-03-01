#ifndef GREEDYBFS_H
#define GREEDYBFS_H

#include "../graph.h"
#include <iostream>
#include <climits>

template<typename TV, typename TE>

class Greedy{
    
    private:
        Graph<TV,TE>* graph;
        UnDirectedGraph<TV,TE> greedy_graph;
        string id_inicial;
        string id_meta;
        unordered_map<string,TV> tabla_h;
        unordered_map<string,string> tabla_padres;
        unordered_map<string,bool> tabla_used;
        unordered_map<string,int> vect_mapheuristics;
        vector<int> heuristics;

        string extraerMinimo(){
            int val = INT_MAX;
            string id_min;
            for (auto iter_n = tabla_h.begin(); iter_n != tabla_h.end(); iter_n++){
                // cout <<  "Se utilizól valor o no?: " << tabla_used[iter_n ->first] << endl;;
                if (iter_n -> second < val && tabla_used[iter_n ->first] == false){
                    id_min = iter_n -> first;
                    val = iter_n -> second;
                }
            }

            return id_min;
        }


    public:
        Greedy(Graph<TV,TE>* _graph, string _id_inicial, string _id_meta,vector<int> _heuristics) : graph(_graph), id_inicial(_id_inicial), id_meta(_id_meta), heuristics(_heuristics) {
            int cont = 0;
            for (auto iter = graph -> vertexes.begin(); iter != graph -> vertexes.end(); iter++){
                vect_mapheuristics[iter -> first] = cont; 
                cont++;    
            }
        };
        ~Greedy() = default;

        UnDirectedGraph<TV,TE> apply(){
            // F(n) -> Distancia del nodo actual [n] hacia el deseado - Heurística
            Vertex<TV,TE>* vert =  graph -> vertexes.find(id_inicial) -> second;
            string vert_id = vert -> id;
            tabla_h[vert_id]  = 0 +  vert -> data; // Se considera data como la heurística ( 0 + H(n) = F(n) )
            bool reach_flag = false; // 
            while (!reach_flag){
                // Indicar vértice a utilizar
                tabla_used[vert_id] = true;
                greedy_graph.insertVertex(vert_id, graph -> vertexes[vert_id] -> data);
                // Añadir sus aristas e incluir el valor F(n)
                for (auto edge : graph -> vertexes[vert_id] -> edges){
                    string  vert_next = (edge -> vertexes[1] -> id != vert_id) ?
                            edge -> vertexes[1] -> id : edge -> vertexes[0] -> id;

                    if (tabla_h.find(vert_next) == tabla_h.end()){
                        tabla_padres[vert_next] = vert_id;
                        tabla_h[vert_next]  = heuristics[vect_mapheuristics[vert_next]];//  F(n) = H(n)
                        tabla_used[vert_next] = false;

                    }
                    else{ 
                        if (tabla_used[vert_next] != true){
                            // Almacenar valores previos 
                            string prev_padre = tabla_padres[vert_next];
                            // Ahora cambiar y sacar el nuevo valor de Fn
                            tabla_padres[vert_next] = vert_id;
                            TE new_Fn  = heuristics[vect_mapheuristics[vert_next]]; //F(n) = H(n)
                            if (new_Fn < tabla_h[vert_next])
                                tabla_h[vert_next] = new_Fn;
                            else
                                tabla_padres[vert_next] = prev_padre;
                            tabla_used[vert_next] = false;

                        }
                    }
                    
                }

                string new_vert_id = extraerMinimo();
                // Insertar arista
                greedy_graph.createEdge(vert_id, new_vert_id, 1);
                vert_id = new_vert_id;
                if (vert_id == id_meta){
                    tabla_used[vert_id] = true;
                    reach_flag = true;
                }
            }

            return greedy_graph;

        };

        void display(){
            string id_eval = id_meta;
            string text = id_meta;
            while (id_eval != id_inicial){
                id_eval = tabla_padres[id_eval];
                text =  id_eval  + " -> " + text;
            }
            cout << "El camino es: " << text << endl;


        }
};




#endif

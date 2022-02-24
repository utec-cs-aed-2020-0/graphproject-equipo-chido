#ifndef ASTAR_H
#define ASTAR_H

#include "../graph.h"
#include <iostream>
#include <limits>

template<typename TV, typename TE>

class AStar{
    
    private:
        Graph<TV,TE>* graph;
        string id_inicial;
        string id_meta;
        unordered_map<string,TV> tabla_h;
        unordered_map<string,string> tabla_padres;
        unordered_map<string,bool> tabla_used;

        TE calcular_Gn(string vert_id){
            string id_eval = vert_id;
            TE Gn_value = 0;
             
            // cout << "Calculo de Gn" << endl; 
            while (id_eval != id_inicial){
                string prev_id_eval = tabla_padres[id_eval];
                // cout << "El padre de " << id_eval << " es " << prev_id_eval << endl;
            //     // Distancia desde id_inical hasta id_eva 
                Vertex<TV,TE>* prev_vert = graph -> vertexes[prev_id_eval];

                for (auto edge : prev_vert -> edges){ 
                    // cout << edge -> vertexes[0] -> id << ", " << edge -> vertexes[1] -> id << endl;
                    if ((edge -> vertexes[0] -> id == id_eval && edge -> vertexes[1] -> id == prev_id_eval )  || 
                        (edge -> vertexes[1] -> id == id_eval && edge -> vertexes[0] -> id == prev_id_eval )){
                            Gn_value = Gn_value + edge -> weight;
                            // cout << Gn_value << endl;
                    }
                }

                id_eval = prev_id_eval;
            }
            return Gn_value;
        }

        string extraerMinimo(){
            int val = std::numeric_limits<int>::max();
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
        AStar(Graph<TV,TE>* _graph, string _id_inicial, string _id_meta) : graph(_graph), id_inicial(_id_inicial), id_meta(_id_meta) {};
        ~AStar() = default;

        void apply_search(){
            // G(n) -> Distancia desde el nodo inicial hacia el nodo actual [n]
            // F(n) -> Distancia del nodo actual [n] hacia el deseado - Heurística
            Vertex<TV,TE>* vert =  graph -> vertexes.find(id_inicial) -> second;
            string vert_id = vert -> id;
            tabla_h[vert_id]  = 0 +  vert -> data; // Se considera data como la heurística ( 0 + H(n) = F(n) )
            bool reach_flag = false; // 
            while (!reach_flag){
                // Indicar vértice a utilizar
                tabla_used[vert_id] = true;
                // Añadir sus aristas e incluir el valor F(n)
                for (auto edge : graph -> vertexes[vert_id] -> edges){
                    string  vert_next = (edge -> vertexes[1] -> id != vert_id) ?
                            edge -> vertexes[1] -> id : edge -> vertexes[0] -> id;

                    if (tabla_h.find(vert_next) == tabla_h.end()){
                        tabla_padres[vert_next] = vert_id;
                        tabla_h[vert_next]  = calcular_Gn(vert_next) + graph -> vertexes[vert_next] -> data;  //  G(n) + H(n)
                        tabla_used[vert_next] = false;
                        // cout <<  "Nuevo nodo: " << tabla_padres[vert_next] << " / Nodo Apunta: " << vert_next << "/ F(n) es: " << tabla_h[vert_next] << endl;

                    }
                    else{ 
                        if (tabla_used[vert_next] != true){
                            // Almacenar valores previos 
                            string prev_padre = tabla_padres[vert_next];
                            // Ahora cambiar y sacar el nuevo valor de Fn
                            tabla_padres[vert_next] = vert_id;
                            TE new_Fn  = calcular_Gn(vert_next) + graph -> vertexes[vert_next] -> data;
                            if (new_Fn < tabla_h[vert_next])
                                tabla_h[vert_next] = new_Fn;
                            else
                                tabla_padres[vert_next] = prev_padre;
                            tabla_used[vert_next] = false;
                            // cout <<  "Nodo: " << tabla_padres[vert_next] << " / Nodo Apunta: " << vert_next << "/ F(n) es: " << tabla_h[vert_next] << endl;

                        }
                    }
                    
                }

                vert_id = extraerMinimo();
                // cout << vert_id << endl;
                if (vert_id == id_meta){
                    tabla_used[vert_id] = true;
                    reach_flag = true;
                }
            }
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
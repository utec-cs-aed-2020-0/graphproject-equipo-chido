#ifndef FLOYD_H
#define FLOYD_H

#include "../graph.h"
#include <iostream>
#include <limits>

using namespace std;


template<typename TV, typename TE>
// Implementación del algoritmo Floyd-Warshall
class Floyd{

    private:
        Graph<TV,TE>* graph;
        unordered_map<string, int> vertex_pos;
        int size_vert;
        TE** mat_dist; 
        string** mat_recorr;
        string* name_vectores;

    public:
        Floyd(Graph<TV,TE>* _graph) : graph(_graph){
            // Inicializar los vértices
            int contador = 0;
            this -> size_vert = graph -> vertexes.size();
            name_vectores = new string[this -> size_vert];
            for (auto iter = graph -> vertexes.begin(); iter != graph -> vertexes.end(); ++iter){
                    vertex_pos[iter -> first] = contador;
                    name_vectores[contador] = iter -> first;
                    contador++;
            }

            /* Verificar inicialización de la posición de los vectores */
            // for (auto iter = vertex_pos.begin(); iter != vertex_pos.end(); ++iter)
            //     cout << "Para el vértice " << iter -> first << " la posición es " << iter -> second << endl;


            // Inicializar las matrices
            mat_dist = new TE*[size_vert];
            mat_recorr = new string*[size_vert];

            for (int n = 0; n < size_vert;n++){
                mat_dist[n] = new TE[size_vert];
                mat_recorr[n] = new string[size_vert];
            }

            // Inicializar todo con Infinito y la diagonal con 0 
            for (int i = 0; i < size_vert;i++){
                for (int j = 0; j < size_vert;j++){
                    if (i == j){
                        mat_dist[i][j] = 0;
                        mat_recorr[i][j] = "-";
                    }
                    else{
                        mat_recorr[i][j] = name_vectores[j];
                        mat_dist[i][j] = std::numeric_limits<TE>::max();
                    }
                }
            }


        };
        ~Floyd() = default;

        void apply(){
            
            // Inicializar la matriz de distancias con los valores de cada edge
            for (auto iter_v = graph->vertexes.begin(); iter_v != graph->vertexes.end();iter_v++){
                for (auto edge: iter_v -> second -> edges){ 
                    string id_begin = iter_v -> first;

                    string  id_finish = (edge -> vertexes[1] -> id != id_begin) ?
                         edge -> vertexes[1] -> id : edge -> vertexes[0] -> id;

                    int pos_id_begin = vertex_pos[id_begin];
                    int posd_id_finish =  vertex_pos[id_finish];
                    mat_dist[pos_id_begin][posd_id_finish] = edge -> weight;
                };
            };

            TE max_val = std::numeric_limits<TE>::max();
            // Realizar evaluación de distancias
            for (int k = 0; k < size_vert; k++){
                for(int i = 0; i < size_vert; i++){
                    for (int j = 0; j < size_vert; j++){
                        if(mat_dist[i][k] != max_val  && mat_dist[k][j] != max_val){ 
                            TE dist_new = mat_dist[i][k] + mat_dist[k][j];
                            if (mat_dist[i][j] > dist_new){
                                mat_dist[i][j] = mat_dist[i][k] + mat_dist[k][j];
                                mat_recorr[i][j] = name_vectores[k];
                            }
                        }
                    }
                }
            }
        };


    void display(){
        TE max_val = std::numeric_limits<TE>::max();

        /* Posicion de los vértices*/

        /* Verificar inicialización de las matriz de distancias */
        cout << "\nMatriz de distancias: " << endl;

        for (int i = 0; i < size_vert;i++){
            cout << name_vectores[i] << "| ";
            for (int j = 0; j < size_vert;j++){
                if (mat_dist[i][j] == max_val)
                    cout << "- ";
                else 
                    cout << mat_dist[i][j] << " ";
            }
            cout << endl;
        }
        /* Verificar inicialización de las matriz de recorridos */
        cout << "\nMatriz de recorridos: " << endl;
        for (int i = 0; i < size_vert;i++){
            cout << name_vectores[i] << "| ";
            for (int j = 0; j < size_vert;j++){
                    cout << mat_recorr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void show_path(string from, string to){
        string init = from;
        cout << "\nLa trayectoria es: ";
        while (init != to){
            cout << init << " -> ";
            init = mat_recorr[vertex_pos[init]][vertex_pos[to]];
        }
        cout << init << endl; ;
    }
};


#endif
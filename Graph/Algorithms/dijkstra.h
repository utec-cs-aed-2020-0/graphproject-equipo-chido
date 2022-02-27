#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph.h"
#include <climits>

template <typename TV, typename TE>
class Dijkstra {
    public:
        unordered_map<Vertex<TV, TE>*, string> ids;
        unordered_map<Vertex<TV, TE>*, Vertex<TV, TE>*> parents;
        unordered_map<Vertex<TV, TE>*, int> distancia;
        Graph<TV,TE> * graph;
        string start_id;

        Dijkstra(Graph<TV,TE>* _graph, string id){
            graph = _graph;
            start_id = id;
        }
        void apply(){
            int cant = graph->vertexes.size();
            unordered_map<Vertex<TV, TE>*, bool> visited;
            for (auto& v : graph->vertexes) {
                distancia[v.second] = INT_MAX;
                visited[v.second] = false;
                ids[v.second] = v.first;
            }
            distancia[graph->vertexes[start_id]] = 0;

            bool flag = true;
            Vertex<TV, TE>* analizando;
            int aux_analizando = INT_MAX;

            while(cant--){
                aux_analizando = INT_MAX;
                for(auto& v : distancia){
                    if(v.second<aux_analizando && !visited[v.first]){
                        analizando = v.first;
                        aux_analizando = v.second;
                    }
                }
                //cout<<"analizando: "<<analizando->id<<endl;
                visited[analizando] = true;
                for(auto& e: analizando->edges){
                    Vertex<TV, TE>* other = e->vertexes[0] != analizando ? e->vertexes[0] : e->vertexes[1];
                    //cout<<"distancia actual: "<<distancia[other]<<endl;
                    if (distancia[analizando] + e->weight < distancia[other]){
                        //cout<<"actualizada a: "<<distancia[analizando] + e->weight<<endl;
                        distancia[other] = distancia[analizando] + e->weight;
                        parents[other] = analizando;
                    }
                }

                aux_analizando = 0;
                for (auto& aux : visited) {
                    if (aux.second == false) {
                        aux_analizando++;
                    }
                }
                flag = (aux_analizando!=0)? true: false;
            }
            
        }

        void display(){
            cout<<"Distancias desde "<<start_id<<" hacia: "<<endl;
            
            for (auto &vertex : graph->vertexes) 
                if (vertex.first!=start_id && distancia[vertex.second]!=INT_MAX)
                    cout<<"Vertice: "<<vertex.first<<" -> distancia: "<<distancia[vertex.second]<<" pasando por "<<ids[parents[vertex.second]]<<endl;
                else if(distancia[vertex.second]==INT_MAX)
                    cout<<"Vertice: "<<vertex.first<<" -> no se puede llegar a este vertice"<<endl;
        }
};
#endif

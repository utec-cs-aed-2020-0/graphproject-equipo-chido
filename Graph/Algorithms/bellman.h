#ifndef BELLMAN_H
#define BELLMAN_H

#include <climits>
#include "../DirectedGraph.h"

template <typename TV, typename TE>
class Bellman {
public:
    DirectedGraph <TV, TE> *graph;
    string start_id;
    unordered_map<string, int> distancia;
    unordered_map<Vertex<TV, TE>*, string> ids;
    unordered_map<string, string> predecesor;

    Bellman(DirectedGraph <TV, TE>* _graph, string id) {
        graph = _graph;
        start_id = id;
    }

    void apply() {
        for (auto &v : graph->vertexes) {
            distancia[v.first] = (v.first == start_id)? 0: INT_MAX;
            ids[v.second] = v.first;
        }

        vector<Edge<TV, TE> *> edges;
        for (auto &v : graph->vertexes) {
            for (auto &edge : v.second->edges) {
                bool found = false;
                for (int i = 0; i < edges.size(); ++i) {
                    if (edges[i] == edge) {
                        found = true;
                        break;
                    }
                }
                if (!found) 
                    edges.push_back(edge);
            }
        }

        for (int i = 0; i < graph->vertexes.size() - 1; i++) {
            for (auto e: edges) {
                auto u=ids[e->vertexes[0]], v= ids[e->vertexes[1]];
                if (distancia[u] != INT_MAX) {
                    if (distancia[v] > distancia[u] + e->weight) {
                        distancia[v] = distancia[u] + e->weight;
                        predecesor[v] = u;
                    }
                }

            }
        }
    }

    void display(){
        cout<<"Distancias desde "<<start_id<<" hacia: "<<endl;
            
        for (auto &vertex : graph->vertexes) 
            if (vertex.first!=start_id)
                cout<<"Vertice: "<<vertex.first<<" -> distancia: "<<distancia[vertex.second->id]<<" pasando por "<<predecesor[vertex.second->id]<<endl;
    }
};
#endif
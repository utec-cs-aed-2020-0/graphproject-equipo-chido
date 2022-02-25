#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../graph.h"
#include "../../DS/ds.h"
#include "../../DS/dsarray.h"
#include <vector>
#include <algorithm>

template <typename TV, typename TE>
class Kruskal {
    public:
        UnDirectedGraph<TV, TE> *graph;
        UnDirectedGraph<TV, TE> *Krus_graph;
        DisjoinSet<Vertex<TV, TE>*>* bosque;
        
        unordered_map<Vertex<TV, TE>*, int> vertexesIndex;
        vector< pair<TE, Edge<TV, TE>*> > edges;


        Kruskal(UnDirectedGraph<TV, TE>* graph) {
            this->graph = graph;
            this->Krus_graph = new UnDirectedGraph<TV, TE>;

            vector<Vertex<TV, TE>*> vertexes;
            
            int i = 0; 
            for (auto& v : graph->vertexes){
                this->Krus_graph->insertVertex(v.second->id, v.second->data);
                vertexes.push_back(v.second);
                vertexesIndex[v.second] = i;
                i++; 
            }

            //inicializar el bosque con los vertices
            this->bosque = new DisjoinSetArray<Vertex<TV, TE>*>(vertexes);            
        }

        void apply() {
            //ponemos las aristas en un vector y ordenarlas
            for (auto& v : this->vertexesIndex)
                for (auto& e : v.first->edges)
                    this->edges.push_back(make_pair((*e).weight, &(*e)));

            sort(this->edges.begin(), this->edges.end());

            //Recorrer las aristas en orden
            for (auto& e : this->edges) {
                int v1 = vertexesIndex[(e.second)->vertexes[0]];
                int v2 = vertexesIndex[(e.second)->vertexes[1]];
                //Verificamos si ambos vertices aun no han sido unidos
                if (this->bosque->Find(v1) != this->bosque->Find(v2)){
                    //Las unimos en el disjoint set y en el grafo
                    this->bosque->Union(v1,v2);
                    Krus_graph->createEdge((e.second)->vertexes[0]->id, (e.second)->vertexes[1]->id, e.first);
                }
            }
        }
        void display(){
            Krus_graph -> display();
        }
};
#endif

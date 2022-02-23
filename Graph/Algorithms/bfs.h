#ifndef BFS_H
#define BFS_H

#include "../graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>

template<typename TV, typename TE>

class BFS{
    
    private:
        Graph<TV,TE>* graph;
        string id_inicial;
        vector<Vertex<TV, TE> *> BFSapplied;


    public:
        BFS(Graph<TV,TE>* _graph, string _id_inicial) : graph(_graph), id_inicial(_id_inicial) {
            BFSapplied = apply();
        }; 
        ~BFS() = default;

        vector<Vertex<TV, TE> *> apply() {
            if (!this->graph->isConnected()) {
            throw("BFS no se puede aplicar");
            }
            vector<Vertex<TV, TE> *> result;

            unordered_map<Vertex<TV, TE> *, bool> visited;
            auto it = this->graph->vertexes.begin();
            while (it != this->graph->vertexes.end()) {
            visited[it->second] = false;
            it++;
            }

            std::list<Vertex<TV, TE> *> queue;
            visited[this->graph->vertexes[this->id_inicial]] = true;

            queue.push_back(this->graph->vertexes[this->id_inicial]);

            while (!queue.empty()) {
            Vertex<TV, TE> *s = queue.front();
            result.push_back(s);
            queue.pop_front();

            for (auto it = s->edges.begin(); it != s->edges.end(); ++it) {
                if (!visited[(*it)->vertexes[0]]) {
                visited[(*it)->vertexes[0]] = true;
                queue.push_back((*it)->vertexes[0]);
                }
                if (!visited[(*it)->vertexes[1]]) {
                visited[(*it)->vertexes[1]] = true;
                queue.push_back((*it)->vertexes[1]);
                }
            }
            }
            return result;
        }

        void display(){
            cout<<"Camino más corto desde: "<<id_inicial<<" -> ";
            for(int i=0; i<BFSapplied.size();i++){
                cout<<BFSapplied[i]->id<<" ("<<BFSapplied[i]->data<<") ";
            }
            cout<<endl;
        }



};




#endif

#ifndef BFS_H
#define BFS_H

#include "../graph.h"
#include <queue>
#include <unordered_map>

using namespace std;

template<typename TV, typename TE>
class BFS {
private:
	DirectedGraph<TV, TE>* BFSapplied = new DirectedGraph<TV,TE>() ;
public:
	BFS(DirectedGraph<TV, TE>* graph, string start) {
		unordered_map<TV, string> help;
		for (auto it = graph->vertexes.begin(); it != graph->vertexes.end(); it++) {
            help[it->second->data] = it->first;
		}

		std::unordered_map<TV, TV> visited;
		queue<TV> resQ;
		TV aux = graph->vertexes.find(start)->second->data;
		resQ.push(aux);
		visited[aux] = aux;
		string auxS = help.find(aux)->second;
		this->BFSapplied->insertVertex(auxS, aux);
		TV aux2 = aux;
		while (!resQ.empty()) {
			aux = resQ.front();
			resQ.pop();
			auxS = help.find(aux)->second;
			for (auto it2 = graph->vertexes.find(auxS)->second->edges.begin(); it2 != graph->vertexes.find(auxS)->second->edges.end(); it2++) {
				aux2 = (*it2)->vertexes[1]->data;
                //cout<<"analizando: "<<auxS<<endl;
				if (visited.find(aux2) == visited.end()) {
					visited[aux2] = aux2;
					resQ.push(aux2);
					this->BFSapplied->insertVertex(help.find(aux2)->second, aux2);
					this->BFSapplied->createEdge(auxS, help.find(aux2)->second, (*it2)->weight);
                    //cout<<"conectando con: "<<(*it2)->vertexes[1]->id<<endl;
				}
			}
		}
	}

	~BFS() = default;
	Graph<TV,TE>* get_graph(){return BFSapplied;}

        void display(){
            BFSapplied -> display();
        }
};

#endif

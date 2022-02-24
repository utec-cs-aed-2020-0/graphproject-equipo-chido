#ifndef DSARRAY_H
#define DSARRAY_H

#include "ds.h"

template <typename T>
class DisjoinSetArray: public DisjoinSet<T>
{
private:
    T *data;
    int *rank, *parent, n, s=0;
public:
    DisjoinSetArray(vector<T> data){
        n = data.size();
        rank = new int[n];
        parent = new int[n];
        this->data = new T[n];
        for (int i=0; i<n; i++){
            this->data[i] = data[i];
            MakeSet(i);
        }
    }

    ~DisjoinSetArray(){
        delete [] rank, parent, data;
        n=0;
    }

    //MakseSet the element with index x
    void MakeSet(int x){
        parent[x]=x;
        rank[x]=0;
        s++;
    }

    //Find the root of x (with optimization by rank)
    int Find(int x){
        if (parent[x] == x)
            return x;
        else
            return Find(parent[x]);
    }

    //Find the root of x (with optimization path compression)
    int FindPathCompression(int x){
        if (parent[x] != x)
            parent[x] = FindPathCompression(parent[x]);
        return parent[x];
    }

    //Union two sets represented by x and y (apply rank)
    void Union(int x, int y){
        if(!isConnected(x,y)){
            int xRoot = FindPathCompression(x), yRoot = FindPathCompression(y);
            if(rank[xRoot]<rank[yRoot])
                parent[xRoot] = yRoot;
            else if(rank[xRoot]>rank[yRoot])
                parent[yRoot] = xRoot;
            else{
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
            s--;
        }
    }
    
    //check whether there is a path between x and y
    bool isConnected(int x, int y){return FindPathCompression(x) == FindPathCompression(y);}

    //total number of elements
    int size(){return n;}

    //number of sets
    int sets(){return s;}

    //total number of elements that belong to the set of x
    int size(int x){
        int aux=0;
        int p = FindPathCompression(x);
        for (int i=0; i<n; i++){
            if(parent[i] == p){
                aux++;
            }
        }
        return aux;
    } //Complejidad = O(n)

    //add the element to the set of x
    void add(T element, int x){
        data[n]=element;
        MakeSet(n);
        Union(n,x);
        n++;
    }
    
    //return all elements that belong to the set of x
    vector<T> getElementsSet(int x){
        vector<T> aux;
        int p = FindPathCompression(x);
        for (int i=0; i<n; i++){
            if(parent[i] == p){
                aux.push_back(data[i]);
            }
        }
        return aux;
    }//Complejidad = O(n)
};

#endif
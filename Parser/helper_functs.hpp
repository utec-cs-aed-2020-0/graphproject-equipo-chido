#ifndef HELPER_FUNCTS_HPP
#define HELPER_FUNCTS_HPP

#include "nlohmann/json.hpp"
#include <cmath>
using namespace std;

using json = nlohmann::json;

//Calcula la distancia euclidiana entre dos latitudes y longitudes
long double distance(string lat1, string long1, string lat2, string long2){
    long double lat_1 = stoi(lat1);
    long double long_1 = stoi(long1);           // se convierten las latitudes y longitudes
    long double lat_2 = stoi(lat2);             // a long doubles para calcular la distancia
    long double long_2 = stoi(long2);

    long double ans = sqrt(pow(long_1 - long_2, 2) + pow(lat_1 - lat_2, 2));

    return ans;
}

//Encuentra la ubicación de un aeropuerto en el jsonGraph teniendo como base el AirportID

int findByAirportID(json jsonGraph, string id) {
    for (int i = 0; i < jsonGraph.size(); i++) {
        if (jsonGraph[i]["Airport ID"] == id)
            return i;
    }
    return 15;                              // si no existe el destino, retorna un valor por defecto
}

#endif // HELPER_FUNCTS_HPP

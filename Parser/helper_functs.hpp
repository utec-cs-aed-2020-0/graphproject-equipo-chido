#ifndef HELPER_FUNCTS_HPP
#define HELPER_FUNCTS_HPP

#define PI_V 3.14159265358979323846  /* Valor de PI*/
#define G2R PI_V/180.0 /* Conversión de Grados a Radianes*/ 

#include "nlohmann/json.hpp"
#include <cmath>
using namespace std;

// for convenience
using json = nlohmann::json;

/////////////////////////////////////////////////////////////////////
/////////////////// Funciones de ayuda /////////////////////////////

//para calcular la distancia entre dos latitudes y longitudes

double distance(string lat_1, string lon_1, string lat_2, string lon_2)
{
    double lat1 = stod(lat_1);
    double lon1 = stod(lon_1);           // se convierten las latitudes y longitudes
    double lat2 = stod(lat_2);             // a long doubles para calcular la distancia
    double lon2 = stod(lon_2);

    double radio_tierra = 6371;
    double a;
    // Convert all  values in radians
    lon2 = lon2*G2R;
    lon1 = lon1*G2R;
    lat1 = lat1*G2R;
    lat2 = lat2*G2R;

    // Fórmula
    a = pow(sin((lat2 - lat1) / 2), 2) +  pow(sin((lon2 - lon1) / 2), 2) *  cos(lat1) * cos(lat2);
    return radio_tierra * 2 * asin(sqrt(a));
}

// funcion para encontrar la ubicación de un aeropuerto en el jsonGraph teniendo como base el AirportID

int findByAirportID(json jsonGraph, string id) {
    for (int i = 0; i < jsonGraph.size(); i++) {
        if (jsonGraph[i]["Airport ID"] == id)
            return i;
    }
    cout << id << endl;
    return 15;                              // si no existe el destino, retorna 0
}

#endif // HELPER_FUNCTS_HPP

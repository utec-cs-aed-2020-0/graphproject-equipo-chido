#include <iostream>
#include <cmath>

#define PI_V 3.14159265358979323846  /* Valor de PI*/
#define G2R PI_V/180.0 /* Conversión de Grados a Radianes*/ 
using namespace std;
 
double haversine(double lat_1, double lon_1, double lat_2, double lon_2)
{
        double radio_tierra = 6371;
        double a;
        // Convert all  values in radians
        lon_2 = lon_2*G2R;
        lon_1 = lon_1*G2R;
        lat_1 = lat_1*G2R;
        lat_2 = lat_2*G2R;
 
        // Fórmula
        a = pow(sin((lat_2 - lat_1) / 2), 2) +  pow(sin((lon_2 - lon_1) / 2), 2) *  cos(lat_1) * cos(lat_2);
        return radio_tierra * 2 * asin(sqrt(a));
}
 

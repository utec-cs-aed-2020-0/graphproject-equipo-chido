#include "haversine.h"

// Driver code
int main()
{
    double lat1 = 51.5007;
    double lon1 = 0.1246;
    double lat2 = 40.6892;
    double lon2 = 74.0445;
     
    cout << haversine(lat1, lon1, lat2, lon2) << " K.M.";
    return 0;
}
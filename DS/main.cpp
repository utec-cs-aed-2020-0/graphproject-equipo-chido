#include <iostream>
#include <algorithm>
#include <vector>       

#include "tester.h"
#include "dstree.h"
#include "dsarray.h"

using namespace std;

void test(vector<char> data, DisjoinSet<char>* ds){    
    ASSERT(ds->sets() == 8, "The function sets is not working");
    ds->Union(0, 2);
    ds->Union(5, 6);
    ds->Union(1, 6);
    ds->Union(7, 0);
    ds->Union(4, 3);
    ASSERT(ds->sets() == 3, "The function sets is not working");
    ASSERT(ds->isConnected(1, 5) == true, "The function isConnected is not working");
    ASSERT(ds->isConnected(2, 4) == false, "The function isConnected is not working");
    ASSERT(ds->isConnected(0, 6) == false, "The function isConnected is not working");
    
    vector<char> set1 = ds->getElementsSet(3);
    sort(set1.begin(), set1.end());
    ASSERT(set1[0] == 'd', "The function getElementsSet is not working");
    ASSERT(set1[1] == 'e', "The function getElementsSet is not working");
    
    ASSERT(ds->size(5) == 3, "The function size(x) is not working");

    ds->Union(2, 5);
    ds->Union(3, 1);
    ASSERT(ds->sets() == 1, "The function sets is not working");
    
    delete ds;
}

int main()
{    
    vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};  
    test(data, new DisjoinSetArray<char>(data));
    //test(data, new DisjoinSetTree<char>(data));
    return 0;
}

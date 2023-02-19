#include <iostream>
#include "Map.h"
#include <vector>
using namespace std;
int main() {
    string fileNamer = "sw_baltic.map";

    //sw_baltic.map
    Map *mp = new Map();
    MapLoader::loadMap(*mp,fileNamer);
    cout << *mp;
    delete mp;
    return 0;
}

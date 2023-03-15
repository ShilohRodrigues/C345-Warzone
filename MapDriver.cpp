#include <iostream>
#include "Map.h"
#include <vector>
using namespace std;
int mapDemo1() {
    string fileNamer = "sw_baltic.map";

    //sw_baltic.map
    Map *mp = new Map();
    MapLoader::loadMap(*mp,fileNamer);
    cout << *mp;
    delete mp;
    return 0;
}
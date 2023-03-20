#include <iostream>
#include "Map.h"
#include <vector>
using namespace std;
int mapDemo1() {
    string fileNamer = "/Users/user/Dropbox/Concordia University/Year 2/Winter 2023/COMP 345/Project_copy/C345-Warzone/canada.map";

    //sw_baltic.map
    Map *mp = new Map();
    MapLoader::loadMap(*mp,fileNamer);
    cout << *mp;
    delete mp;
    return 0;
}
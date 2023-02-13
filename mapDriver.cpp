#include "map.h"
#include <iostream>
using namespace std;


int main() {
    string fileNamer;
    cout << "Please enter Directory for your .map file , if the map is in the same directory please enter the file name" << endl;
    cin >> fileNamer;
    //sw_baltic.map
    MapLoader mp = MapLoader(fileNamer);
}
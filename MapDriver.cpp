#include "Map.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
    
    string path = "sw_baltic.map";
    //cout << "Please enter the path for your .map file , if the map is in the same directory please enter the file name:" << endl;
    //cin >> path;
    Map mp = MapLoader::loadMap(path); //Call static loadMap method, return a map object

    cout << endl << mp;
    cout << endl << endl;
    mp.printContinents();

    cout << endl;
    if (mp.validate()) cout << "Map Validated!" << endl;
    else cout << "Map Invalid";

}

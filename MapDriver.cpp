#include "Map.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
    
    string path = "";
    cout << "Please enter the path for your .map file , if the map is in the same directory please enter the file name:" << endl;
    cin >> path;
    Map mp = MapLoader::loadMap(path); //Call static loadMap method, return a map object

    Territory *t = new Territory(3, "Canada");

    cout << *t;

}

#include "Map.h"

////////////// Territory Class /////////////////////
//Parameterized
Territory::Territory(int tid, string tname) {
    id = shared_ptr<int> (new int(tid));;
    name = shared_ptr<string> (new string(tname)); 
    armyCnt = shared_ptr<int> (new int(0));
}   
//Copy
Territory::Territory(Territory &territory) {
    id = territory.id;
    name = territory.name;
    armyCnt = territory.armyCnt;
}   
//Destructor
Territory::~Territory() {

}  
//Assignment
Territory& Territory::operator=(const Territory& territory) {
    if (this == &territory) return *this;
    this->name = territory.name;
    this->id = territory.id;
    this->armyCnt = territory.armyCnt;
    return *this;
}
//Stream Insertion
ostream& operator<<(ostream &strm, const Territory &t) {
    return strm << "ID: " << *t.id << endl << "Continent Name: " << *t.name << endl << "Army Count: " << *t.armyCnt << endl;
}

int Territory::getId() {
    return *id;
}

////////////// Continent Class /////////////////////
//Parameterized
Continent::Continent(int cid, string cname) {
    id = shared_ptr<int> (new int(cid));
    name = shared_ptr<string> (new string(cname)); 
}
//Copy
Continent::Continent(Continent &continent) {
    id = continent.id;
    name = continent.name;
    territories = continent.territories;
}   
//Destructor
Continent::~Continent() {
    //delete[] territories;
}  
//Assignment
Continent& Continent::operator=(const Continent& continent) {
    if (this == &continent) return *this;
    this->name = continent.name;
    this->id = continent.id;
    this->territories = continent.territories;
    return *this;
}  
//Stream Insertion
ostream& operator<<(ostream &strm, const Continent &c) {
   return strm << endl;
}

void Continent::addBorder(Territory from, list<Territory> to) {
    (*territories)[from] = to;
}


//MAPLOADER CLASS 
//Helper function to split strings by the separator char.  
vector<string> split(string str, char separator) {
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

//Static function that loads parses a map file and returns a map object
Map MapLoader::loadMap(string path) {

    ifstream mapFile(path);

    if (!mapFile.is_open()) {
        cout << "Error: Unable to open file" << endl;
        throw std::runtime_error("Error: Unable to open file");
    }

    string line = "";
    while (getline(mapFile, line)) {
        if (line == "[continents]") {
            int count = 0;
            while (getline(mapFile, line) && !line.empty()) {
                //Split the line into the ID and the Name
                vector<string> sLine = split(line, ' ');
                string name = sLine[0]; 
                //Create Continent ***********
                new Continent(++count, name);
            }

        }

        if (line == "[countries]") {
            while (getline(mapFile, line) && !line.empty()) {             
                //Split the line into the ID and the Name
                vector<string> sLine = split(line, ' ');
                int id = stoi(sLine[0]);
                string name = sLine[1];              
                //Create new territory
                new Territory(id, name);
            }
        }

        if (line == "[borders]") {
            while (getline(mapFile, line) && !line.empty()) {
                
            }
        }
    }

    Map *mp = new Map();
    return *mp;

}

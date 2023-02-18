#include "Map.h"

//Custom hashing function
size_t MyHash::operator()(Territory const& t) const noexcept {
    size_t h1 = hash<int>{}(t.getId());
    size_t h2 = hash<string>{}(t.getName());
    return h1 ^ (h2 << 1); 
}
size_t MyHash::operator()(Continent const& c) const noexcept {
    size_t h1 = hash<int>{}(c.getId());
    size_t h2 = hash<string>{}(c.getName());
    return h1 ^ (h2 << 1); 
}

////////////// Territory Class /////////////////////
//Parameterized
Territory::Territory(int tid, string tname, int tcontId) {
    id = tid;
    name = tname;
    continentId = tcontId; 
    armyCnt = 0;
}   
//Copy
Territory::Territory(const Territory &territory) {
    id = territory.id;
    name = territory.name;
    continentId = territory.continentId;
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
    this->continentId = territory.continentId;
    return *this;
}
//Equals Operator
bool Territory::operator==(const Territory& territory) const {
    if (this->id == territory.id && this->name == territory.name) return true;
    else return false;
}
//Stream Insertion
ostream& operator<<(ostream &strm, const Territory &t) {
    return strm << t.id << ": " << t.name;
}

int Territory::getId() const {
    return id;
}
string Territory::getName() const {
    return name;
}
int Territory::getContId() const {
    return continentId;
}

////////////// Continent Class /////////////////////
//Parameterized
Continent::Continent(int cid, string cname) {
    id = cid;
    name = cname; 
    territories = new unordered_map<Territory, list<Territory>, MyHash>();
}
//Copy
Continent::Continent(const Continent &continent) {
    id = continent.id;
    name = continent.name;
    territories = new unordered_map<Territory, list<Territory>, MyHash>(*continent.territories);
}   
//Destructor
Continent::~Continent() {
    delete territories;
}  
//Assignment
Continent& Continent::operator=(const Continent& continent) {
    if (this == &continent) return *this;
    this->name = continent.name;
    this->id = continent.id;
    this->territories = continent.territories;
    return *this;
} 
//Equals Operator
bool Continent::operator==(const Continent& continent) const {
    if (this->id == continent.id && this->name == continent.name) return true;
    else return false;
} 
//Stream Insertion
ostream& operator<<(ostream &strm, const Continent &c) {
   strm << c.id << ": " << c.name << endl;
   //Loop through the map keys 
    strm << "Territory ID: Name -> Adjacent Territories" << endl;
    for (auto i = c.territories->begin(); i != c.territories->end(); i++) { 
       strm << i->first << " --> ";
       //Loop through the adjacent territories
       for (auto const& j : i->second) {
            strm << j << ", ";
       }
       strm << endl;
    } 
    return strm << endl;
}
//Id getter
int Continent::getId() const {
    return id;
}
//Name getter
string Continent::getName() const {
    return name;
}
//Get territories
unordered_map<Territory, list<Territory>, MyHash> Continent::getTerritories() {
    return *territories;
}
//Add territory and their borders
void Continent::addBorder(Territory from, list<Territory> to) {
    (*territories)[from] = to;
}

//////////////// Map Class //////////////////////
//Default
Map::Map() {
    territories = new unordered_map<Territory, list<Territory>, MyHash>();
    continents = new vector<Continent>();
}
//Copy
Map::Map(Map &map) {
    territories = new unordered_map<Territory, list<Territory>, MyHash>(*map.territories);
    continents = new vector<Continent>(*map.continents);
}   
//Destructor
Map::~Map() {
    delete territories;
    delete continents;
}  
//Assignment
Map& Map::operator=(const Map& map) {
    if (this == &map) return *this;
    this->territories = map.territories;
    this->continents = map.continents;
    return *this;
} 
//Stream Insertion
ostream& operator<<(ostream &strm, const Map &m) {
    //Loop through the map keys 
    strm << "Territory ID: Name -> Adjacent Territories" << endl;
    for (auto i = m.territories->begin(); i != m.territories->end(); i++) { 
       strm << i->first << " --> ";
       //Loop through the adjacent territories
       for (auto const& j : i->second) {
            strm << j << ", ";
       }
       strm << endl;
    } 
    return strm << endl;
}
//Add territory and their borders
void Map::addBorder(Territory from, list<Territory> to) {
    (*territories)[from] = to;
}
//Add a continent
void Map::addContinent(Continent c) {
    continents->push_back(c);
}
//Add a border for a continent
void Map::addBorderContinent(int cid, Territory from, list<Territory> to) {
    (*continents)[cid].addBorder(from, to);
}
//Print the continents vector 
void Map::printContinents() {
    for (auto const& j : *continents) {
        cout << j;
    }
}
//Check if the territories are a connected graph and if every continent is a connected subgraph
bool Map::validate() {
    
    bool valid = true;

    //Validating that the map is a connected graph
    if (!isConnected(*territories)) valid = false;
    //Validate that the continents are connected subgraphs
    for (auto &j : *continents) {
        if (!isConnected(j.getTerritories())) valid = false;
    }

    return valid;
}
//Helper function: performs breadth first traversal checks if everythings connected
bool Map::isConnected(unordered_map<Territory, list<Territory>, MyHash> territories) {
    if (territories.empty()) {
        return false; // empty map is not connected
    } 
    //to track visited territories
    unordered_set<Territory, MyHash> visited;
    queue<Territory> q;

    q.push(territories.begin()->first);
    visited.insert(q.front());
    while (!q.empty()) {
        Territory current = q.front();
        q.pop();
        for (auto adjacent : territories[current]) {
            if (visited.count(adjacent) == 0) {
                q.push(adjacent);
                visited.insert(adjacent);
            }
        }
    }
    //Check if all territories were visited
    return visited.size() == territories.size();
}

//MapLoader Class 
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

    unique_ptr<Map> mp(new Map());
    vector<Territory> territories;

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
                //Create Continent add it to vector of continents
                Continent *c = new Continent(++count, name);
                mp->addContinent(*c);
                delete c;
            }
        }

        if (line == "[countries]") {
            while (getline(mapFile, line) && !line.empty()) {             
                //Split the line into the ID and the Name
                vector<string> sLine = split(line, ' ');
                int id = stoi(sLine[0]);
                string name = sLine[1];  
                int continentId = stoi(sLine[2]);            
                //Create Continent add it to vector of continents
                Territory *t = new Territory(id, name, continentId);
                territories.push_back(*t);
                delete t;
            }
        }

        if (line == "[borders]") {
            while (getline(mapFile, line) && !line.empty()) {
                //Split the line into separate country ids
                vector<string> sLine = split(line, ' ');
                Territory from = territories[stoi(sLine[0])-1];
                int c_id = from.getContId(); //Get continent id of current country
                //For the map object
                list<Territory> to;
                //For the continent object
                list<Territory> toC;

                //Loops through the borders to create
                for(int i=1; i<sLine.size(); i++) {
                    try {
                        to.push_back(territories[stoi(sLine[i])-1]);
                        //Check if the continents of the adjacent territory is the same to add to continent list
                        if (c_id == territories[stoi(sLine[i])-1].getContId()) {
                            toC.push_back(territories[stoi(sLine[i])-1]);
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        //Skip invalid integer
                    }
                }
                //Adds the territory to the map territories unordered_map
                mp->addBorder(from, to);
                mp->addBorderContinent(c_id-1, from, toC);
            }
        }
    }

    return *mp;

}

#include "Map.h"

#include <utility>
#include <regex>

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

Territory::Territory(int idTerritory, const string& territoryName, int territoryContinent){
    id = std::make_unique<int>(idTerritory);
    name = std::make_unique<string>(territoryName);
    continentId = std::make_unique<int>(territoryContinent);
    armyCnt = std::make_unique<int>(0);
    playerInPossession = std::make_unique<string>("");
}
//Parameterized
Territory::Territory(int idTerritory, const string& territoryName, int territoryContinent, const string& player,int armies) {
    id = std::make_unique<int>(idTerritory);
    name = std::make_unique<string>(territoryName);
    continentId = std::make_unique<int>(territoryContinent);
    playerInPossession = std::make_unique<string>(player);
    armyCnt = std::make_unique<int>(armies);
}

//Copy
Territory::Territory(const Territory &territory) {
    id = std::make_unique<int>(*territory.id);
    name = std::make_unique<string>(*territory.name);
    continentId = std::make_unique<int>(*territory.continentId);
    playerInPossession = std::make_unique<string>(*territory.playerInPossession);
    armyCnt = std::make_unique<int>(*territory.armyCnt);
}
//Destructor
Territory::~Territory() = default;
//Assignment
Territory& Territory::operator=(const Territory& territory) {
    if(this == &territory) {return *this;}
    /* Smart pointers automatically manage for memory leaks therefor we would not have to
       delete pointers*/
    name.reset();
    id.reset();
    playerInPossession.reset();
    armyCnt.reset();
    continentId.reset();
    // Allocate new memory and copy over the data from the other object
    name = std::make_unique<string>(*territory.name);
    continentId = std::make_unique<int>(*territory.continentId);
    armyCnt = std::make_unique<int>(*territory.armyCnt);
    playerInPossession = std::make_unique<string>(*territory.playerInPossession);
    // This is a pointer that deals with our current object, by returning this, we are returning the
    //current object
    return *this;
}
//Equals Operator
bool Territory::operator==(const Territory& territory) const {
    if (this->id == territory.id && this->name == territory.name) return true;
    else return false;
}
//Stream Insertion
ostream& operator<<(ostream &os, const Territory &t) {
    //If territoryInfo.playerInPossession == null run this
    if(t.playerInPossession == nullptr) {
        os << " Territory Name: " << *t.name <<
           ", Continent ID: " << *t.continentId
           << ", Armies: " << *t.armyCnt << endl;
    }
    else{
        os << "Territory Name: " << *t.name <<
           ", Continent: " << *t.continentId
           << ", Player on territory: " << *t.playerInPossession
           << ", Armies: " << *t.armyCnt << endl;
    }
    return os;
}

int Territory::getId() const {
    return *id;
}
string Territory::getName() const {
    return *name;
}
int Territory::getContId() const {
    return *continentId;
}

const unique_ptr<string> &Territory::getPlayerInPossession() const {
    return playerInPossession;
}

void Territory::setPlayerInPossession(unique_ptr<string> &playerInPossession) {
    Territory::playerInPossession = std::move(playerInPossession);
}

const unique_ptr<int> &Territory::getArmyCnt() const {
    return armyCnt;
}

void Territory::setArmyCnt(unique_ptr<int> &armyCnt) {
    Territory::armyCnt = std::move(armyCnt);
}

////////////// Continent Class /////////////////////
//Parameterized
Continent::Continent(int cid, const string& cname) {
    name = std::make_unique<string>(cname);
    id = std::make_unique<int>(cid);
    territories = new unordered_map<Territory, list<Territory>, MyHash>();
}
//Copy
Continent::Continent(const Continent &continent) {
    name = std::make_unique<string>(*continent.name);
    id = std::make_unique<int>(*continent.id);
    territories = new unordered_map<Territory, list<Territory>, MyHash>(*continent.territories);
}
//Destructor
Continent::~Continent() = default;


//Assignment
Continent& Continent::operator=(const Continent& ct) {
    if (this == &ct) return *this;
    name = std::make_unique<string>(*ct.name);
    id = std::make_unique<int>(*ct.id);
    territories = new unordered_map<Territory, list<Territory>, MyHash>(*ct.territories);
    return *this;
}
//Equals Operator
bool Continent::operator==(const Continent& continent) const {
    if (this->id == continent.id && this->name == continent.name) return true;
    else return false;
}
//Stream Insertion
ostream& operator<<(ostream &strm, const Continent &c) {
    strm << *c.id << ": " << *c.name << endl;
    //Loop through the map keys
    strm << "Territory ID: Name -> Adjacent Territories" << endl;
    for (auto & territorie : *c.territories) {
        strm << territorie.first << " --> ";
        //Loop through the adjacent territories
        for (auto const& j : territorie.second) {
            strm << j << ", ";
        }
        strm << endl;
    }
    return strm << endl;
}
//Id getter
int Continent::getId() const {
    return *id;
}
//Name getter
string Continent::getName() const {
    return *name;
}
//Get territories
unordered_map<Territory, list<Territory>, MyHash> Continent::getTerritories() {
    return *territories;
}
//Add territory and their borders
void Continent::addBorder(const Territory& from, list<Territory> to) {
    (*territories)[from] = std::move(to);
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
    for (auto & territorie : *m.territories) {
        strm << territorie.first << " --> ";
        //Loop through the adjacent territories
        for (auto const& j : territorie.second) {
            strm << j << ", ";
        }
        strm << endl;
    }
    return strm << endl;
}
//Add territory and their borders
void Map::addBorder(const Territory& from, list<Territory> to) {
    (*territories)[from] = std::move(to);
}
//Add a continent
void Map::addContinent(const Continent& c) {
    continents->push_back(c);
}
//Add a border for a continent
void Map::addBorderContinent(int cid, const Territory& from, list<Territory> to) {
    (*continents)[cid].addBorder(from, std::move(to));
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
bool Map::isConnected(unordered_map<Territory, list<Territory>, MyHash> t) {
    if (t.empty()) {
        return false; // empty map is not connected
    }
    //to track visited territories
    unordered_set<Territory, MyHash> visited;
    queue<Territory> q;

    q.push(territories->begin()->first);
    visited.insert(q.front());
    while (!q.empty()) {
        Territory current = q.front();
        q.pop();
        for (const auto& adjacent : t[current]) {
            if (visited.count(adjacent) == 0) {
                q.push(adjacent);
                visited.insert(adjacent);
            }
        }
    }
    //Check if all territories were visited
    return visited.size() == territories->size();
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
bool MapLoader::loadMap(Map& mp, const string& path) {

    ifstream mapFile(path);
    int count = 0;

    vector<Territory> territoriesMapLoader;

    if (!mapFile.is_open()) {
        cout << "Error: Unable to open file" << endl;
        return false;
    }

    string line = " ";
    while (getline(mapFile, line)) {
        line = std::regex_replace(line, std::regex(R"(\r\n|\r|\n)"), "");
        if (line == "[continents]") {
            while (getline(mapFile, line) && !line.empty()) {
                line = std::regex_replace(line, std::regex(R"(\r\n|\r|\n)"), "");
                if (line.empty()) {
                    break;
                }
                //Split the line into the ID and the Name
                vector<string> sLine = split(line, ' ');
                string name = sLine[0];
                //Create Continent add it to vector of continents
                auto *c = new Continent(++count, name);
                mp.addContinent(*c);
            }
        }

        if (line == "[countries]") {
            while (getline(mapFile, line) && !line.empty()) {
                line = std::regex_replace(line, std::regex(R"(\r\n|\r|\n)"), "");
                if (line.empty()) {
                    break;
                }
                //Split the line into the ID and the Name
                vector<string> sLine = split(line, ' ');
                int id = stoi(sLine[0]);
                string name = sLine[1];
                int continentId = stoi(sLine[2]);
                //Create Continent add it to vector of continents
                auto *t = new Territory(id, name, continentId);
                territoriesMapLoader.push_back(*t);
            }
        }

        if (line == "[borders]") {
            while (getline(mapFile, line) && !line.empty()) {
                line = std::regex_replace(line, std::regex(R"(\r\n|\r|\n)"), "");
                if (line.empty()) {
                    break;
                }
                //Split the line into separate country ids
                vector<string> sLine = split(line, ' ');
                //ERROR STARTING HERE
                Territory  from = territoriesMapLoader[stoi(sLine[0])-1];
                int c_id = from.getContId(); //Get continent id of current country
                //For the map object
                list<Territory> to;
                //For the continent object
                list<Territory> toC;

                //Loops through the borders to create
                for(int i=1; i<sLine.size(); i++) {
                    try {
                        to.push_back(territoriesMapLoader[stoi(sLine[i])-1]);
                        //Check if the continents of the adjacent territory is the same to add to continent list
                        if (c_id == territoriesMapLoader[stoi(sLine[i])-1].getContId()) {
                            toC.push_back(territoriesMapLoader[stoi(sLine[i])-1]);
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        //Skip invalid integer
                    }
                }
                //Adds the territory to the map territories unordered_map
                mp.addBorder(from, to);
                mp.addBorderContinent(c_id-1, from, toC);
            }
        }
    }
    mapFile.close();
    return true;
}
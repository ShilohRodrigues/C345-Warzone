#include "map.h"

using namespace std;
//CLASS PLAYER 
Player::Player(const string& x) {
    name = x;
}
Player::~Player() {}
string Player::getName() { return name; }



//CLASS TERRITORY ************************************************************************************************************************
//Constructor Territory 
Territory::Territory(int idTerritory, string usrName, string usrContinent, shared_ptr<Player> currentPlayer, int armyCount) {
    territoryId = unique_ptr<int>(new int(idTerritory));
    name = unique_ptr<string>(new string(usrName));
    belongsToContinent = unique_ptr<string>(new string(usrContinent));
    playerInPossession = shared_ptr<Player>(currentPlayer);
    armies = unique_ptr<int>(new int(armyCount));
}
Territory::Territory(int idTerritory, string usrName, string usrContinent) {
    territoryId = unique_ptr<int>(new int(idTerritory));
    name = unique_ptr<string>(new string(usrName));
    belongsToContinent = unique_ptr<string>(new string(usrContinent));
    playerInPossession = nullptr;
    armies = unique_ptr<int>(new int(0));
}
ostream& operator<<(std::ostream& os, const Territory& territoryInfo) {
    os << "Name: " << *territoryInfo.name <<
        ", Continent: " << *territoryInfo.belongsToContinent
        << ", Player: " << territoryInfo.playerInPossession->getName()
        << ", Armies: " << *territoryInfo.armies << endl;
    return os;
}

Territory::~Territory() {
    /*  Since we have smart pointers, "delete" pointers would not be required nor would it work in our scenario,
        as smart pointers delete themselves.*/

        /*  Although smart pointers deallocate memories themselves, we can use .reset() to ensure that our pointers are
            destroyed. Since we have unique_ptr's we can be certain that when destroying these pointers, we wont have
            any dangling pointers;
        */
    name.reset();
    belongsToContinent.reset();
    playerInPossession.reset();
    armies.reset();
}

Territory& Territory::operator=(const Territory& copiedTerritory) {
    /* Smart pointers automatically manage for memory leaks therefor we would not have to
       delete pointers*/
    name.reset();
    belongsToContinent.reset();
    playerInPossession.reset();
    armies.reset();
    // Allocate new memory and copy over the data from the other object
    name = unique_ptr<string>(new string(*copiedTerritory.name));
    belongsToContinent = unique_ptr<string>(new string(*copiedTerritory.belongsToContinent));
    armies = unique_ptr<int>(new int(*copiedTerritory.armies));
    playerInPossession = shared_ptr<Player>(new Player(*copiedTerritory.playerInPossession));
    // This is a pointer that deals with our current object, by returning this, we are returning the 
    //current object 
    return *this;
}
void Territory::setName(const string& newName) {
    *name = newName;
}
void Territory::setContinent(const string& newContinent) {
    *belongsToContinent = newContinent;
}
void Territory::setArmy(int armyCount) {
    *armies = armyCount;
}
void Territory::setNeighbours(Territory* N) {
    adjacent.push_back(N);
}
//mutator functions 
int Territory::getTerritoryID() const {
    return *territoryId;
}
string Territory::getTerritoryName() const {
    return *name;
}
string Territory::getContinent() const {
    return *belongsToContinent;
}
int Territory::getArmyCount() const {
    return *armies;
}




//CLASS CONTINENTS ********************************************************************************************************************************
Continent::Continent(string continentName, int idContinent) {
    name = unique_ptr<string>(new string(continentName));
    continentID = unique_ptr<int>(new int(idContinent));
}

Continent::~Continent() {}

void Continent::addTerritory(Territory* A) {
    territories.push_back(A);
}

string Continent::getContinentName() {
    return *name;
}
int Continent::getContinentID() {
    return *continentID;
}





//CLASS MAP ***************************************************************************************************************************
//constructor and deconstructor
Map::Map() {}
Map::~Map() {}

//mutator functions
void Map::addTerritory(Territory* A) {
    territories.push_back(A);
    territoryMap[A->getTerritoryName()] = A;

}
void Map::addContinent(Continent* A) {
    continents.push_back(A);
    continentMap[A->getContinentName()] = A;
}
void Map::connectTerritories(string A, string B) {
    Territory* territory1 = territoryMap[A];
    Territory* territory2 = territoryMap[B];
    territory1->setNeighbours(territory2);
    territory2->setNeighbours(territory1);
}

//accessor functions 
string Map::getContinentFromContinentId(int id) {
    for (Continent* c : continents) {
        if (c->getContinentID() == id) {
            return c->getContinentName();
        }
        else {
            return "NOT A CONTINENT";
        }
    }
    return "";
}

bool Map::isConnectedMap() {
    vector<Territory*> currentTerritories = territories;
    while (currentTerritories.size() > 0) {
        auto neighbour = currentTerritories[0];
        int index = std::distance(territories.begin(), find(territories.begin(), territories.end(), neighbour));

        for (int i = 0; i < neighbour->getAdjacent().size(); i++) {
            auto& nextTerritory = neighbour->getAdjacent()[i];
            if (find(currentTerritories.begin(), currentTerritories.end(), nextTerritory) != currentTerritories.end()) {
                int index = std::distance(territories.begin(), find(territories.begin(), territories.end(), nextTerritory));
            }
        }
    }

    return currentTerritories.size() == 0;
}


//******************************************************
//README*************************************************
//NEED TO IMPLEMENT INONECONTINENT**************************
//***********************************************************


//MAPLOADER CLASS ******************************************************************************
MapLoader::MapLoader(const string& fileName) {
    ifstream mapFile(fileName);
    int continentCounter = 0;

    if (!mapFile.is_open()) {
        cout << "Error: Unable to open file" << endl;
        throw std::runtime_error("Error: Unable to open file");
    }

    string line;
    while (getline(mapFile, line)) {
        if (line == "[continents]") {
            while (getline(mapFile, line) && !line.empty()) {
                continentCounter++;
                istringstream getWord(line);
                string continentName;
                getWord >> continentName;
                Continent* newContinent = new Continent(continentName, continentCounter);
                mp->addContinent(newContinent);
            }
        }

        if (line == "[countries]") {
            while (getline(mapFile, line) && !line.empty()) {
                istringstream getWord(line);
                int countryID, continentId;
                string countryName, continentName;
                getWord >> countryID >> countryName >> continentId;
                continentName = mp->getContinentFromContinentId(continentId);
                //Create Object Territory.
                Territory* newTerritory = new Territory(countryID, countryName, continentName);

                //push territory into class Map's vector territories
                mp->addTerritory(newTerritory);

                //push territory into class Continent vector territories
                for (Continent* ct : mp->getContinents()) {
                    if (ct->getContinentID() == continentId) {
                        ct->addTerritory(newTerritory);
                    }
                }
            }
        }

        if (line == "[borders]") {
            while (getline(mapFile, line) && !line.empty()) {
                istringstream getWord(line);
                string getBorders, continentId;
                std::stringstream getInt(line);
                int node, first;
                getInt >> first;


                Territory* currentTerritory = nullptr;
                for (Territory* TT : mp->getTerritories()) {
                    if (TT->getTerritoryID() == first) {
                        currentTerritory = TT;
                        break;
                    }

                }
                while (getInt >> node) {
                    for (Territory* TF : mp->getTerritories()) {
                        if (TF->getTerritoryID() == node) {
                            currentTerritory->setNeighbours(TF);
                            break;
                        }
                    }
                }
            }
        }
    }
}

#ifndef MAP_H 
#define MAP_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <stack>
//TESTER CLASS OFF GITHUB, NOT PART OF THE ASSIGNMENT CRITERIA *********************
using namespace std;
class Player {
private:
    string name;                         //player name

public:
    Player();                            //default constructor
    Player(const string&);              //one parameter constructor
    Player(const Player*);               //copy constructor DELETE***********************
    Player& operator = (const Player&);  //assignment operator DELETE ***************************************
    ~Player();                           //destructor

    string getName();                    //accessor
    void setName(string);                //mutator
};
//TESTER CLASS END ********************************************


//Class TERRITORY ***********************************************************************************
//Territory Class 
class Territory {
private:
    unique_ptr<std::string> name;
    unique_ptr<std::string> belongsToContinent;
    shared_ptr<Player> playerInPossession;
    unique_ptr<int> armies;
    unique_ptr<int> territoryId;
    vector<Territory*> adjacent;

public:
    //Constructors and Destructors
    Territory(int, string, string, shared_ptr<Player>, int);
    Territory(int, string, string);
    Territory(const Territory&);
    ~Territory();
    Territory& operator=(const Territory&);

    /* Stream insertion "<<" is not a member of our class, it belongs to <iostream>.
       Therefor to work with Stream insertion our operator overloading */
    friend std::ostream& operator<<(std::ostream&, const Territory&);


    //Accessor functions 
    void setName(const string&);
    void setContinent(const string&);
    void setArmy(int);
    void setNeighbours(Territory*);

    //mutator functions 
    int getTerritoryID() const;
    string getTerritoryName() const;
    string getContinent() const;
    int getArmyCount() const;
    vector<Territory*> getAdjacent() const { return adjacent; }

    //NEED TO UPDATE WITH EUGENIE'S CLASS 
    // Player getPlayer() const; 
    //void setPlayer(Player*);
};


//Class CONTINENT ******************************************************************************
class Continent {
private:
    unique_ptr<string>name;
    unique_ptr<int>continentID;
    vector<Territory*> territories;
public:
    Continent(string, int);
    ~Continent();

    void addTerritory(Territory*);

    string getContinentName();
    int getContinentID();
    //FOR BOOL isConnectedContinent ONLYYY
    vector<Territory*> getTerritories() const { return territories; }
};

//class MAP ***********************************************************************
class Map {
public:
    vector<Territory*> territories;
    vector<Continent*> continents;
    map<string, Territory*> territoryMap;
    map<string, Continent*> continentMap;

    Map(); //default constructor
    ~Map();

    //mutator functions
    void addTerritory(Territory*);
    void addContinent(Continent*);
    void connectTerritories(string, string);


    //boolean functions
    bool isConnectedMap();
    bool isConnectedContinents();
    bool inOneContinent(string);

    //accessor function
    string getContinentFromContinentId(int);
    vector<Continent*> getContinents() const { return continents; }
    vector<Territory*> getTerritories() const { return territories; }
};

class MapLoader {
private:
    shared_ptr<Map> mp;

public:
    MapLoader(const string&);
};

#endif

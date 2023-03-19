#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

struct MyHash;
class Territory;
class Continent;
class Map;
class MapLoader;

//Custom hashing function for territory and continent
struct MyHash {
    size_t operator()(Territory const& t) const noexcept;
    size_t operator()(Continent const& c) const noexcept;
};

class Territory {

private:
    unique_ptr<int> id;
    unique_ptr<std::string> name;
    unique_ptr<string> playerInPossession;
    unique_ptr<int> continentId;
    unique_ptr<int> armyCnt;

public:
    //Initial territory
    Territory(int, const string&, int);
    Territory(int , const string& , int , const string& , int );
    Territory(const Territory &territory); //Copy Constructor
    ~Territory(); //Destructor
    Territory& operator=(const Territory& territory); //Assignment Operator
    bool operator==(const Territory& territory) const; //Equals Operator
    friend ostream& operator<<(ostream& strm, const Territory& t); //Stream Insertion Operator

    int getId() const; //ID getter
    string getName() const; //Name getter
    int getContId() const;
    // part 3 add//
    const unique_ptr<string> &getPlayerInPossession() const;
    void setPlayerInPossession(unique_ptr<string> &playerInPossession);

    const unique_ptr<int> &getArmyCnt() const;
    void setArmyCnt(unique_ptr<int> &armyCnt);

};

class Continent {

private:
    unique_ptr<string>name;
    unique_ptr<int>id;
    unordered_map<Territory, list<Territory>, MyHash> *territories;

public:
    Continent(int cid, const string& cname); //Parameterized Constructor
    Continent(const Continent &continent); //Copy Constructor
    ~Continent(); //Destructor
    Continent& operator=(const Continent& continent); //Assignment Operator
    bool operator==(const Continent& continent) const; //Equals Operator
    friend ostream& operator<<(ostream& strm, const Continent& c); //Stream Insertion Operator

    int getId() const; //ID getter
    string getName() const; //Name getter
    unordered_map<Territory, list<Territory>, MyHash> getTerritories();
    void addBorder(const Territory& from, list<Territory> to);

};

class Map {

private:
    vector<Continent> *continents;
    unordered_map<Territory, list<Territory>, MyHash> *territories;

public:
    Map();
    Map(Map &Map); //Copy Constructor
    ~Map(); //Destructor
    Map& operator=(const Map& map); //Assignment Operator
    friend ostream& operator<<(ostream& strm, const Map& m); //Stream Insertion Operator

    void addBorder(const Territory& from, list<Territory> to);
    void addContinent(const Continent& c);
    void addBorderContinent(int cid, const Territory& from, list<Territory> to);
    void printContinents();
    bool validate();
    bool isConnected(unordered_map<Territory, list<Territory>, MyHash> territories);
    // part 3 add//
    vector<Continent>& getContinents();

};

class MapLoader {

public:
    static void loadMap(Map& ,const string& path);

};

int mapDemo1();

#endif
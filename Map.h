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
        int id;
        string name;
        int continentId;
        int armyCnt;

    public:
        Territory(int tid, string tname, int tcontId); //Parameterized Constructor
        Territory(const Territory &territory); //Copy Constructor
        ~Territory(); //Destructor
        Territory& operator=(const Territory& territory); //Assignment Operator 
        bool operator==(const Territory& territory) const; //Equals Operator 
        friend ostream& operator<<(ostream& strm, const Territory& t); //Stream Insertion Operator

        int getId() const; //ID getter
        string getName() const; //Name getter
        int getContId() const;

};

class Continent {

    private:
        int id;
        string name;
        unordered_map<Territory, list<Territory>, MyHash> *territories;

    public:
        Continent(int cid, string cname); //Parameterized Constructor
        Continent(const Continent &continent); //Copy Constructor
        ~Continent(); //Destructor
        Continent& operator=(const Continent& continent); //Assignment Operator 
        bool operator==(const Continent& continent) const; //Equals Operator    
        friend ostream& operator<<(ostream& strm, const Continent& c); //Stream Insertion Operator

        int getId() const; //ID getter
        string getName() const; //Name getter
        void addBorder(Territory from, list<Territory> to);

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

        void addBorder(Territory from, list<Territory> to);
        void addContinent(Continent c);
        void addBorderContinent(int cid, Territory from, list<Territory> to);
        void printContinents();
        bool validate();

};

class MapLoader {

    public:
        static Map loadMap(string path);

};

#endif

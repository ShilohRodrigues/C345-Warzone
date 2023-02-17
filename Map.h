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

class Territory {

    private:
        shared_ptr<int> id;
        shared_ptr<string> name;
        shared_ptr<int> armyCnt;

    public:
        Territory(int tid, string tname); //Parameterized Constructor
        Territory(Territory &territory); //Copy Constructor
        ~Territory(); //Destructor
        Territory& operator=(const Territory& territory); //Assignment Operator 
        friend ostream& operator<<(ostream& strm, const Territory& t); //Stream Insertion Operator

        int getId(); //ID getter

};

class Continent {

    private:
        shared_ptr<int> id;
        shared_ptr<string> name;
        unordered_map<Territory, list<Territory>> *territories;

    public:
        Continent(int cid, string cname); //Parameterized Constructor
        Continent(Continent &continent); //Copy Constructor
        ~Continent(); //Destructor
        Continent& operator=(const Continent& continent); //Assignment Operator     
        friend ostream& operator<<(ostream& strm, const Continent& c); //Stream Insertion Operator

        void addBorder(Territory from, list<Territory> to);

};

class Map {

    private:
        //Graph of Continents

    public:
        // Map();                                                    //Default Constructor
        // Map(/*Graph of continents*/);                            //Parameterized Constructor
        // Map(Map &Map);                                //Copy Constructor
        // ~Map();                                                   //Destructor
        // Map& operator=(const Map& map);               //Assignment Operator     
        // friend ostream& operator<<(ostream& strm, const Map& m);  //Stream Insertion Operator

        //Add Continent

};

class MapLoader {

    public:
        static Map loadMap(string path);

};

#endif

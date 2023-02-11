#pragma once
#include<vector> // To implement a list containing orders.
#include<iostream> // For input/output.
#include<iomanip> // To format output.
#include<string> // To store the label of an order within the order object itself.
#include"../HeaderFiles/Map.h"
#include"../HeaderFiles/Player.h"
#include"../HeaderFiles/Cards.h"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::istream;
using std::setw;
using std::setfill;
using std::left;
using std::string;

/**
 * This is an abstract class for orders. All functionalities meant to be implemented by subclasses.
 */
class Order // ORDER MIGHT NEED ID IN THE FUTURE
{
public:
    Order();
    Order(const Order&);
    
    friend ostream& operator<<(ostream& out, const Order& o);
    friend istream& operator>>(istream& in, Order&);
    
    virtual string getLabel() const = 0;
    virtual bool validate() const = 0;
    virtual void execute() const = 0;
    virtual ~Order() = 0;

private:
    virtual Order* clone() const = 0;
    virtual ostream& printOrder(ostream&) const = 0;

    friend class OrdersList;
};

class deploy : public Order
{
public:
    deploy();
    deploy(Player*, Territory*, const int&);
    deploy(const deploy&);
    deploy& operator=(const deploy);

    friend ostream& operator<<(ostream& out, const deploy& d);
    friend istream& operator>>(istream& in, deploy&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~deploy();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;

    //NEW: Attributes of type Player, Territory and int
    
    Player* player; //Player who issued order
    Territory* target; //Territory being deployed to
    int reinforcements; //Number of reinforcements from the Reinforcement pool

};


class advanceOrder : public Order
{
public:
    advanceOrder();
    advanceOrder(Player* player, Territory* source, Territory* target, Player* enemy, const int&);
    advanceOrder(const advanceOrder&);
    advanceOrder& operator=(const advanceOrder);

    friend ostream& operator<<(ostream& out, const advanceOrder& a);
    friend istream& operator>>(istream& in, advanceOrder&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~advanceOrder();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;

    //NEW: Attributes of type Player, Territory and int

    Player* player;       //Player performing the order
    Territory* source;    //Territory owned by the player
    Territory* target;    //Territory owned by the enemy player
    Player* enemy;        //Player who owns the target enemy
    int numberArmies;    //Number of armies to be sent
};

class bomb : public Order
{
public:
    bomb();
    bomb(Player*, Territory*, Hand*, Deck*);
    bomb(const bomb&);
    bomb& operator=(const bomb);

    friend ostream& operator<<(ostream& out, const bomb& b);
    friend istream& operator>>(istream& in, bomb&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~bomb();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;

    //NEW: Attributes of type Player, Territory, Hand, and Deck

    Player* player;
    Territory* target;
    Hand* hand;
    Deck* deck;
};

class blockade : public Order
{
public:
    blockade();
    blockade(const blockade&);
    blockade& operator=(const blockade);

    friend ostream& operator<<(ostream& out, const blockade& b);
    friend istream& operator>>(istream& in, blockade&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~blockade();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class airlift : public Order
{
public:
    airlift();
    airlift(const airlift&);
    airlift& operator=(const airlift);

    friend ostream& operator<<(ostream& out, const airlift& a);
    friend istream& operator>>(istream& in, airlift&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~airlift();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

class negotiate : public Order
{
public:
    negotiate();
    negotiate(const negotiate&);
    negotiate& operator=(const negotiate);

    friend ostream& operator<<(ostream& out, const negotiate& n);
    friend istream& operator>>(istream& in, negotiate&);

    string getLabel() const override;
    bool validate() const override;
    void execute() const override;
    ~negotiate();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
};

/**
 * Should be created at the beginning of the program.
 * Creates an order, the type depending on the user input.
 */
class OrderOperation
{
public:
    OrderOperation();
    OrderOperation(const OrderOperation&);
    OrderOperation& operator=(const OrderOperation);

    ~OrderOperation();

    friend ostream& operator<<(ostream& out, const OrderOperation& o);
    friend istream& operator>>(istream& in, OrderOperation&);

    Order* createOrder(string) const;
};

/**
 * Designed to hold a list of valid orders
 * and carry out basic list functions.
 */
class OrdersList
{
public:
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList&);
    void addOrder(Order* o);
    void remove(int);
    void move(int, int);
    void executeOrders(); // Executes orders and empties the list
    OrdersList& operator=(const OrdersList&);

    friend ostream& operator<<(ostream& out, const OrdersList& o);
    friend istream& operator>>(istream& in, OrdersList&);

private:
    vector<Order*> orders;
   
};

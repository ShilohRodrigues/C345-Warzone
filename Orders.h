#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <list>

using namespace std;

// superclass order
class Order {
public:
    const int orderID; // to keep track of individual orders since they have the same name

    Order();
    // copy constructor
    Order(const Order& order);
    // assignment operator
    Order& operator=(const Order& order);
    // each subclass needs validate(), execute()
    virtual bool validate();
    virtual void execute();
    // stream insertion operator
    friend ostream& operator<<(ostream& os, const Order& order);
private:
    static int nextID; // counter to maintain unique IDs
};

// subclasses
// deploy(), advance(), bomb(), blockade(), airlift(), negotiate()
class Deploy : Order {
public:
    Deploy();
    Deploy(const Deploy& deploy);
    Deploy& operator=(const Deploy& deploy);
    friend ostream& operator<<(ostream& os, const Deploy& deploy);

    bool validate() override;
    void execute() override;
};

class Advance : Order {
public:
    Advance();
    Advance(const Advance& advance);
    Advance& operator=(const Advance& advance);
    friend ostream& operator<<(ostream& os, const Advance& advance);

    bool validate() override;
    void execute() override;
};

class Bomb : Order {
public:
    Bomb();
    Bomb(const Bomb& bomb);
    Bomb& operator=(const Bomb& bomb);
    friend ostream& operator<<(ostream& os, const Bomb& bomb);

    bool validate() override;
    void execute() override;
};

class Blockade : Order {
public:
    Blockade();
    Blockade(const Blockade& blockade);
    Blockade& operator=(const Blockade& blockade);
    friend ostream& operator<<(ostream& os, const Blockade& blockade);

    bool validate() override;
    void execute() override;
};

class Airlift : Order {
public:
    Airlift();
    Airlift(const Airlift& airlift);
    Airlift& operator=(const Airlift& airlift);
    friend ostream& operator<<(ostream& os, const Airlift& airlift);

    bool validate() override;
    void execute() override;
};

class Negotiate : Order {
public:
    Negotiate();
    Negotiate(const Negotiate& negotiate);
    Negotiate& operator=(const Negotiate& negotiate);
    friend ostream& operator<<(ostream& os, const Negotiate& negotiate);

    bool validate() override;
    void execute() override;
};

class OrdersList {
public:
    OrdersList();
    // copy constructor
    OrdersList(const OrdersList& ordersList);
    // assignment operator
    OrdersList& operator=(const OrdersList& ordersList);
    // stream insertion operator
    friend ostream& operator<<(ostream& os, const OrdersList& ordersList);

    void add(shared_ptr<Order> order);
    // move(), remove()
    void move(const string& direction, int orderID);
    void remove(int orderID);

    unique_ptr<list<shared_ptr<Order>>> orderList;
};

void ordersDriver();

#endif // ORDERS_H
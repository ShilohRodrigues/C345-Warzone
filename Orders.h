#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <list>
#include "Player.h"
#include "Map.h"

using namespace std;

class Player;
class Territory;

// superclass order
class Order {
public:
    Order();
    // copy constructor
    Order(const Order& order);
    // assignment operator
    Order& operator=(const Order& order);
    // each subclass needs validate(), execute()
    virtual bool validate()=0;
    virtual void execute()=0;
    // stream insertion operator
    friend ostream& operator<<(ostream& os, const Order& order);

    // getters and setters
    const int getOrderId() const;
    static int getNextId();
    static void setNextId(int nextId);

private:
    const int orderID; // to keep track of individual orders since they have the same name
    static int nextID; // counter to maintain unique IDs
};

// subclasses
// deploy(), advance(), bomb(), blockade(), airlift(), negotiate()
class Deploy : public Order {
public:
    Deploy();
    Deploy(const shared_ptr<Player>& player,
           const shared_ptr<Territory>& targetTerritory,
           int deployedArmies);
    Deploy(const Deploy& deploy);
    Deploy& operator=(const Deploy& deploy);
    friend ostream& operator<<(ostream& os, const Deploy& deploy);

    bool validate() override;
    void execute() override;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(const shared_ptr<Player> &player);

    const shared_ptr<Territory> &getTargetTerritory() const;
    void setTargetTerritory(const shared_ptr<Territory> &targetTerritory);

    int getDeployedArmies() const;
    void setDeployedArmies(int deployedArmies);

private:
    shared_ptr<Player> player;
    shared_ptr<Territory> targetTerritory;
    int deployedArmies;
};

class Advance : public Order {
public:
    Advance();
    Advance(const shared_ptr<Player>& player,
            const shared_ptr<Territory>& sourceTerritory,
            const shared_ptr<Territory>& targetTerritory,
            int advanceArmies);
    Advance(const Advance& advance);
    Advance& operator=(const Advance& advance);
    friend ostream& operator<<(ostream& os, const Advance& advance);

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(const shared_ptr<Player> &player);

    const shared_ptr<Territory> &getSourceTerritory() const;
    void setSourceTerritory(const shared_ptr<Territory> &sourceTerritory);

    const shared_ptr<Territory> &getTargetTerritory() const;
    void setTargetTerritory(const shared_ptr<Territory> &targetTerritory);

    int getAdvanceArmies() const;
    void setAdvanceArmies(int advanceArmies);

    bool validate() override;
    void execute() override;

    void attack();

private:
    shared_ptr<Player> player;
    shared_ptr<Territory> sourceTerritory;
    shared_ptr<Territory> targetTerritory;
    int advanceArmies;
};

class Bomb : public Order {
public:
    Bomb();
    Bomb(const shared_ptr<Player>& player,
         const shared_ptr<Territory>& targetTerritory);
    Bomb(const Bomb& bomb);
    Bomb& operator=(const Bomb& bomb);
    friend ostream& operator<<(ostream& os, const Bomb& bomb);

    bool validate() override;
    void execute() override;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(const shared_ptr<Player> &player);

    const shared_ptr<Territory> &getTargetTerritory() const;
    void setTargetTerritory(const shared_ptr<Territory> &targetTerritory);

private:
    shared_ptr<Player> player;
    shared_ptr<Territory> targetTerritory;
};

class Blockade : public Order {
public:
    Blockade();
    Blockade(const shared_ptr<Player>& player,
             const shared_ptr<Player>& neutralPlayer,
             const shared_ptr<Territory>& targetTerritory);
    Blockade(const Blockade& blockade);
    Blockade& operator=(const Blockade& blockade);
    friend ostream& operator<<(ostream& os, const Blockade& blockade);

    bool validate() override;
    void execute() override;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(const shared_ptr<Player> &player);

    const shared_ptr<Player> &getNeutralPlayer() const;
    void setNeutralPlayer(const shared_ptr<Player> &neutralPlayer);

    const shared_ptr<Territory> &getTargetTerritory() const;
    void setTargetTerritory(const shared_ptr<Territory> &targetTerritory);

private:
    shared_ptr<Player> player;
    shared_ptr<Player> neutralPlayer;
    shared_ptr<Territory> targetTerritory;
};

class Airlift : public Order {
public:
    Airlift();
    Airlift(const shared_ptr<Player>& player,
            const shared_ptr<Territory>& sourceTerritory,
            const shared_ptr<Territory>& targetTerritory,
            int airliftArmies);
    Airlift(const Airlift& airlift);
    Airlift& operator=(const Airlift& airlift);
    friend ostream& operator<<(ostream& os, const Airlift& airlift);

    bool validate() override;
    void execute() override;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(const shared_ptr<Player> &player);

    const shared_ptr<Territory> &getSourceTerritory() const;
    void setSourceTerritory(const shared_ptr<Territory> &sourceTerritory);

    const shared_ptr<Territory> &getTargetTerritory() const;
    void setTargetTerritory(const shared_ptr<Territory> &targetTerritory);

    int getAirliftArmies() const;
    void setAirliftArmies(int airliftArmies);

private:
    shared_ptr<Player> player;
    shared_ptr<Territory> sourceTerritory;
    shared_ptr<Territory> targetTerritory;
    int airliftArmies;
};

class Negotiate : public Order {
public:
    Negotiate();
    Negotiate(shared_ptr<Player> &issuer, shared_ptr<Player> &targetPlayer);
    Negotiate(const Negotiate& negotiate);
    Negotiate& operator=(const Negotiate& negotiate);
    friend ostream& operator<<(ostream& os, const Negotiate& negotiate);

    bool validate() override;
    void execute() override;

    const shared_ptr<Player> &getIssuer() const;
    void setIssuer(const shared_ptr<Player> &issuer);

    const shared_ptr<Player> &getTargetPlayer() const;
    void setTargetPlayer(const shared_ptr<Player> &targetPlayer);

private:
    shared_ptr<Player> issuer; // player issuing the order
    shared_ptr<Player> targetPlayer;
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

    template<typename T>
    void add(shared_ptr<T> order);
    // move(), remove()
    void move(const string& direction, int orderID);
    void remove(int orderID);

    // getters and setters
    const unique_ptr<list<shared_ptr<Order>>> &getOrderList() const;
    void setOrderList(unique_ptr<list<shared_ptr<Order>>> &orderList);

private:
    unique_ptr<list<shared_ptr<Order>>> orderList;
};

void ordersDemo1();
void ordersDemo2();

void deployDemo();
void advanceDemo();
void airliftDemo();
void bombDemo();
void blockadeDemo();
void negotiateDemo();

#endif // ORDERS_H
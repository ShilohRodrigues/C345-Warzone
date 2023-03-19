#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <memory>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;

class OrdersList;

class Player {
public:
    // default constructor
    Player();
    explicit Player(const vector<shared_ptr<Territory>>& territories);
    Player(int armyCount, int reinforcementPool, const vector<shared_ptr<Territory>>& territories);
    // copy constructor
    Player(const Player& player);
    // assignment operator
    Player& operator=(const Player& player);
    // stream insertion operator (friend)
    friend ostream& operator<<(ostream& os, const Player& player);
    // destructor
    ~Player();

    // required methods
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    void issueOrder();

    // extra methods
    void addTerritory(const shared_ptr<Territory>& territory);
    void removeTerritory(const shared_ptr<Territory>& territory);
    void removeTerritory(const shared_ptr<Territory>& territory, const shared_ptr<Player>& newOwner);
    void updateTerritories();

    void addNegotiatedPlayer(const shared_ptr<Player>& player);
    void clearNegotiatedPlayers();
    bool isInNegotiatedPlayers(string playerName);

    int updateArmyCount();

    // getters and setters
    const string &getName() const;

    int getArmyCount() const;
    void setArmyCount(int armyCount);

    int getReinforcementPool() const;
    void setReinforcementPool(int reinforcementPool);

    const unique_ptr<Hand> &getCardHand() const;
    void setCardHand(unique_ptr<Hand> &cardHand);

    const unique_ptr<vector<shared_ptr<Territory>>> &getTerritories() const;
    void setTerritories(unique_ptr<vector<shared_ptr<Territory>>> &territories);

    const unique_ptr<OrdersList> &getOrdersList() const;
    void setOrdersList(unique_ptr<OrdersList> &ordersList);

    const unique_ptr<vector<shared_ptr<Player>>> &getNegotiatedPlayers() const;
    void setNegotiatedPlayers(const unique_ptr<vector<shared_ptr<Player>>> &negotiatedPlayers);

private:
    static int nextID;
    const string name;
    int armyCount; // total army count available to the player
    int reinforcementPool; // armies the player can use every turn, decreases as the player uses them, replenishes later
    // player owns a hand of Warzone cards
    unique_ptr<Hand> cardHand;
    // player owns collection of territories
    unique_ptr<vector<shared_ptr<Territory>>> territories;
    // player has list of orders
    unique_ptr<OrdersList> ordersList;
    // for the negotiation order
    unique_ptr<vector<shared_ptr<Player>>> negotiatedPlayers;
};

void playerDemo1();

#endif // PLAYER_H
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <memory>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;

// player class declarations

class Player {
public:
    string name;
    // default constructor
    Player();
    explicit Player(const vector<shared_ptr<Territory>>& territories);
    // copy constructor
    Player(const Player& player);
    // assignment operator
    Player& operator=(const Player& player);
    // stream insertion operator (friend)
    friend ostream& operator<<(ostream& os, const Player& player);
    // destructor
    ~Player();

    // toDefend()
    // toAttack()
    // issueOrder()

    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    void issueOrder();

// player owns collection of territories
// player owns a hand of Warzone cards
// player has list of orders
    unique_ptr<Hand> cardHand;
private:
    unique_ptr<vector<shared_ptr<Territory>>> territories;
    unique_ptr<OrdersList> ordersList;
};

void playerDriver();

#endif // PLAYER_H
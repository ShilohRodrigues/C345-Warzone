#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "Territory.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;

// player class declarations

class Player {
public:
    // default constructor
    Player();
    explicit Player(vector<Territory*>& territories);
    // copy constructor
    Player(const Player& player);
    // assignment operator
    Player& operator=(const Player& player);
    // stream insertion operator (friend)
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    // destructor
    ~Player();

    // toDefend()
    // toAttack()
    // issueOrder()

    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(Order* order);

// player owns collection of territories
// player owns a hand of Warzone cards
// player has list of orders
private:
    vector<Territory*> territories;
    Hand* cardHand;
    OrdersList* ordersList;
};

#endif // PLAYER_H
#include <vector>
#include <iostream>

#include "Player.h"
#include "Territory.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;

// default constructor
// TODO: see how Territory, Hand, OrdersList constructors are implemented
Player::Player():territories(vector<Territory*> {}), cardHand(new Hand()), ordersList(new OrdersList()) {}

// parameterized constructor (for testing)
Player::Player(vector<Territory*>& territories):territories(territories), cardHand(new Hand()), ordersList(new OrdersList())
{}

// copy constructor
Player::Player(const Player& player) {
    // TODO: verify that Territory, Hand, OrdersList have copy constructors
    for (Territory* t: player.territories) {
        this->territories.push_back(new Territory(*t));
    }
    this->cardHand = new Hand(*player.cardHand);
    this->ordersList = new OrdersList(*player.ordersList);
}

// assignment operator
Player& Player::operator=(const Player& player) {
    if (this == &player) {
        return *this;
    } else {
        territories.clear();
        for (Territory* t: player.territories) {
            this->territories.push_back(new Territory(*t));
        }
        this->cardHand = new Hand(*player.cardHand);
        this->ordersList = new OrdersList(*player.ordersList);
        return *this;
    }
}

// stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    // TODO: verify that Territory, Hand, OrdersList have stream insertion operators
//    os << "Territories:\n";
//    for (Territory* t : player.territories) {
//        os << *t << "\n";
//    }
//    os << "Hand:\n" << player.cardHand;
//    os << "Orders:\n" << player.ordersList;

    os << "test output for stream operator";

    return os;
}

    // destructor
    Player::~Player() {
        for (Territory* t : territories) {
            delete t;
        }
        delete cardHand;
        delete ordersList;
    }


// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
vector<Territory*> Player::toDefend() {
    // returns arbitrary list for now
    return {territories[0], territories[1]};
}

// toAttack()
/**
 * Returns a list of territories to attack.
 * @return list of territories to attack
 */
vector<Territory*> Player::toAttack() {
    // returns arbitrary list for now
    return {territories[2], territories[3]};
}


// issueOrder()
/**
 * Creates an order and adds it to the list of orders.
 * @param order
 */
void Player::issueOrder() {
    // create test order for now
//    Order* testOrder = new Order();
    // TODO: issueOrder(); verify how orders are added to OrdersList
//    ordersList->add(testOrder);
}



#include <vector>
#include <iostream>

#include "Player.h"
#include "Territory.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;

// default constructor
// TODO: see how Territory, Hand, OrdersList constructors are implemented
Player::Player():territories(make_unique<vector<shared_ptr<Territory>>>()), cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

// parameterized constructor (for testing)
Player::Player(const vector<shared_ptr<Territory>>& territories):
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

// copy constructor
Player::Player(const Player& player) {
    // TODO: verify that Territory, Hand, OrdersList have copy constructors and assignment operators
//    for (Territory* t: *player.territories) {
//        this->territories->push_back(new Territory(*t));
//    }
//    this->cardHand = make_unique<Hand>(*player.cardHand);
//    this->ordersList = make_unique<OrdersList>(*player.ordersList);
}

// assignment operator
Player& Player::operator=(const Player& player) {
    if (this == &player) {
        return *this;
    } else {
        territories->clear();
        for (const shared_ptr<Territory>& t: *player.territories) {
            this->territories->push_back(make_shared<Territory>(*t));
        }
        this->cardHand = make_unique<Hand>(*player.cardHand);
        this->ordersList = make_unique<OrdersList>(*player.ordersList);
        return *this;
    }
}

// stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    // TODO: verify that Territory, Hand, OrdersList have stream insertion operators
//    os << "Territories:\n";
//    for (Territory* t : *player.territories) {
//        os << *t << "\n";
//    }
//    os << "Hand:\n" << *player.cardHand;
//    os << "Orders:\n" << *player.ordersList;

    os << "test output for stream operator";

    return os;
}

    // destructor
    Player::~Player() {}


// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toDefend() {
    // returns arbitrary list for now
    auto arbitraryList = make_unique<vector<shared_ptr<Territory>>>();
    arbitraryList->push_back((*territories)[0]);
    arbitraryList->push_back((*territories)[1]);

    return arbitraryList;
}

// toAttack()
/**
 * Returns a list of territories to attack.
 * @return list of territories to attack
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toAttack() {
    // returns arbitrary list for now
    auto arbitraryList = make_unique<vector<shared_ptr<Territory>>>();
    arbitraryList->push_back((*territories)[2]);
    arbitraryList->push_back((*territories)[3]);

    return arbitraryList;
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



#include "Player.h"

using namespace std;

// default constructor
Player::Player(): name("defaultPlayer"), territories(make_unique<vector<shared_ptr<Territory>>>()),
                    cardHand(make_unique<Hand>()),ordersList(make_unique<OrdersList>()) {}

// parameterized constructor (for testing)
Player::Player(const vector<shared_ptr<Territory>>& territories):
    name("defaultPlayer"),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

// copy constructor
Player::Player(const Player& player) {
    this->name = player.name;
    for (const auto& t: *player.territories) {
        this->territories->push_back(t);
    }
    this->cardHand = make_unique<Hand>(*player.cardHand);
    this->ordersList = make_unique<OrdersList>(*player.ordersList);
}

// assignment operator
Player& Player::operator=(const Player& player) {
    // if it's the same as the present player, don't change anything
    if (this == &player) {
        return *this;
    } else {
        // change data members so that they match
        this->name = player.name;
        territories->clear();
        for (const auto& t: *player.territories) {
            this->territories->push_back(t);
        }
        this->cardHand = make_unique<Hand>(*player.cardHand);
        this->ordersList = make_unique<OrdersList>(*player.ordersList);
        return *this;
    }
}

// stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Territories:\n";
    // make sure territories isn't null before iterating over it
    if (player.territories) {
        for (const auto& t : *player.territories) {
            os << *t << endl;
        }
        os << endl;
    } else {
        os << "null\n";
    }

    os << "Hand: " << *player.cardHand;
    os << "Orders: " << *player.ordersList << endl;

    return os;
}

    // destructor
    Player::~Player() = default; // deletion of data members handled by smart pointers already


// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toDefend() {
    // returns arbitrary list for now
    auto arbitraryList = make_unique<vector<shared_ptr<Territory>>>();
    arbitraryList->push_back(this->territories->at(0));
    arbitraryList->push_back(this->territories->at(1));

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
    arbitraryList->push_back(this->territories->at(2));
    arbitraryList->push_back(this->territories->at(3));

    return arbitraryList;
}


// issueOrder()
/**
 * Creates an order and adds it to the list of orders.
 * @param order
 */
void Player::issueOrder() {
    // create test order for now
    auto testOrder = make_shared<Deploy>();
    ordersList->add(testOrder);
}



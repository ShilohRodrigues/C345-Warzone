#include "Player.h"

using namespace std;

int Player::nextID = 0;

// default constructor
Player::Player():
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>()),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

// parameterized constructors (for testing)
Player::Player(const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

Player::Player(int armyCount, int reinforcementPool, const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(armyCount),
    reinforcementPool(reinforcementPool),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()) {}

// copy constructor
Player::Player(const Player& player) {
    this->name = player.name;
    this->armyCount = player.armyCount;
    this->reinforcementPool = player.reinforcementPool;
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
        this->armyCount = player.armyCount;
        this->reinforcementPool = player.reinforcementPool;
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
    os << "name: " << player.name << endl;
    os << "armyCount: " << player.armyCount << endl;
    os << "reinforcementPool: " << player.reinforcementPool << endl;
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

    os << "Hand: " << *player.cardHand << endl;
    os << "Orders: " << *player.ordersList << endl;

    return os;
}

// getters and setters
const string &Player::getName() const {
    return name;
}

void Player::setName(const string &name) {
    Player::name = name;
}

int Player::getArmyCount() const {
    return armyCount;
}

void Player::setArmyCount(int armyCount) {
    Player::armyCount = armyCount;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int reinforcementPool) {
    Player::reinforcementPool = reinforcementPool;
}

const unique_ptr<Hand> &Player::getCardHand() const {
    return cardHand;
}

void Player::setCardHand(unique_ptr<Hand> &cardHand) {
    Player::cardHand = std::move(cardHand);
}

const unique_ptr<vector<shared_ptr<Territory>>> &Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(unique_ptr<vector<shared_ptr<Territory>>> &territories) {
    Player::territories = std::move(territories);
}

const unique_ptr<OrdersList> &Player::getOrdersList() const {
    return ordersList;
}

void Player::setOrdersList(unique_ptr<OrdersList> &ordersList) {
    Player::ordersList = std::move(ordersList);
}

// destructor
Player::~Player() = default; // deletion of data members handled by smart pointers already


// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toDefend() {
    // TODO: not arbitrary anymore
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
    // TODO: not arbitrary anymore
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
    // TODO: not arbitrary anymore
    auto testOrder = make_shared<Deploy>();
    ordersList->add(testOrder);
}



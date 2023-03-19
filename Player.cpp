#include "Player.h"
#include <algorithm>

using namespace std;

int Player::nextID = 0;

// default constructor
Player::Player():
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>()),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()){}

// parameterized constructors (for testing)
Player::Player(const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()){
    setTerritories(this->territories);
}

Player::Player(int armyCount, int reinforcementPool, const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(armyCount),
    reinforcementPool(reinforcementPool),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()){
    setTerritories(this->territories);
}

// copy constructor
Player::Player(const Player& player):
    armyCount(player.armyCount),
    reinforcementPool(player.reinforcementPool),
    territories(make_unique<vector<shared_ptr<Territory>>>()),
    cardHand(make_unique<Hand>(*player.cardHand)),
    ordersList(make_unique<OrdersList>(*player.ordersList)),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()){
    for (const auto& t: *player.territories) {
        this->territories->push_back(t);
    }
}

// assignment operator
Player& Player::operator=(const Player& player) {
    // if it's the same as the present player, don't change anything
    if (this == &player) {
        return *this;
    } else {
        // change data members so that they match
        this->armyCount = player.armyCount;
        this->reinforcementPool = player.reinforcementPool;
        territories->clear();
        for (const auto& t: *player.territories) {
            this->territories->push_back(t);
        }
        this->cardHand = make_unique<Hand>(*player.cardHand);
        this->ordersList = make_unique<OrdersList>(*player.ordersList);
        this->setNegotiatedPlayers(player.negotiatedPlayers);
        return *this;
    }
}

// stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "name: " << player.name << ", ";
    os << "armyCount: " << player.armyCount << ", ";
    os << "reinforcementPool: " << player.reinforcementPool << endl;
    os << "Territories:\n";
    // make sure territories isn't null before iterating over it
    if (player.territories) {
        for (const auto& t : *player.territories) {
            os << *t;
        }
    } else {
        os << "null\n";
    }

    os << "Hand: " << *player.cardHand << endl;
    os << "Orders: " << *player.ordersList << endl;
    os << "negotiatedPlayers:" << endl;
    if (player.negotiatedPlayers) {
        for (const auto& p : *player.negotiatedPlayers) {
            os << "    " << p->getName();
        }
    }

    return os;
}

// getters and setters
const string &Player::getName() const {
    return name;
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
    if (territories) {
        this->territories = std::move(territories);
        for (const auto& territory : *this->territories) {
            auto playerInPossession = make_unique<string>(this->name);
            territory->setPlayerInPossession(playerInPossession);
        }
    }
}

const unique_ptr<OrdersList> &Player::getOrdersList() const {
    return ordersList;
}

void Player::setOrdersList(unique_ptr<OrdersList> &ordersList) {
    Player::ordersList = std::move(ordersList);
}

const unique_ptr<vector<shared_ptr<Player>>> &Player::getNegotiatedPlayers() const {
    return negotiatedPlayers;
}

void Player::setNegotiatedPlayers(const unique_ptr<vector<shared_ptr<Player>>> &negotiatedPlayers) {
    for (const auto& player : *negotiatedPlayers) {
        this->negotiatedPlayers->push_back(player);
    }
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

void Player::addTerritory(const shared_ptr<Territory>& territory) {
    // add territory to territories vector
    this->territories->push_back(territory);

    // change player in possession
    auto playerNamePtr = make_unique<string>(this->name);
    territory->setPlayerInPossession(playerNamePtr);

    // update army count
    this->armyCount += *territory->getArmyCnt();
}

void Player::removeTerritory(const shared_ptr<Territory>& territory) {
    // find the territory
    auto iterator = find_if(this->territories->begin(), this->territories->end(),
                            [territory](const shared_ptr<Territory>& t) {
        return t->getId() == territory->getId();
    });

    if (iterator != this->territories->end()) {
        // territory is found, remove it
        this->territories->erase(iterator);
        // update army count
        this->armyCount -= *territory->getArmyCnt();
    }
}

void Player::removeTerritory(const shared_ptr<Territory> &territory, const shared_ptr<Player> &newOwner) {
    removeTerritory(territory);
    // change player in possession
    auto newOwnerNamePtr = make_unique<string>(newOwner->getName());
    territory->setPlayerInPossession(newOwnerNamePtr);
}

void Player::addNegotiatedPlayer(const shared_ptr<Player>& player) {
    this->negotiatedPlayers->push_back(player);
}

void Player::clearNegotiatedPlayers() {
    this->negotiatedPlayers->clear();
}

bool Player::isInNegotiatedPlayers(string playerName) {
    return any_of(this->negotiatedPlayers->begin(),
                  this->negotiatedPlayers->end(),
                  [&](const auto& player) {
        return player->getName() == playerName;
    });
}

int Player::updateArmyCount() {
    int newArmyCount = 0;
    for (const auto& territory : *this->territories) {
        newArmyCount += *territory->getArmyCnt();
    }
    this->armyCount = newArmyCount;
    return newArmyCount;
}



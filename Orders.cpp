#include "Orders.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <random>

using namespace std;

// for every class:
// default constructor
// copy constructor
// assignment operator
// stream insertion operator

int Order::nextID = 0; // counter to assign unique orderIDs

// default constructor
Order::Order():orderID(++nextID) {}
// copy constructor
Order::Order(const Order& order):orderID(++nextID) {} // should still create unique orderID
// assignment operator - none because the subclasses have their own concrete implementation
// stream insertion operator
ostream& operator<<(ostream& os, const Order& order) {
    os << typeid(order).name();
    os << " - orderID: " << order.orderID;

    return os;
}

const int Order::getOrderId() const {
    return orderID;
}

int Order::getNextId() {
    return nextID;
}

void Order::setNextId(int nextId) {
    nextID = nextId;
}

// Order subclasses
// validate() for every subclass
// execute() for every subclass

// Deploy
Deploy::Deploy():Order() {}
Deploy::Deploy(const shared_ptr<Player>& player,
               const shared_ptr<Territory>& targetTerritory,
               const int deployedArmies):
    player(player), targetTerritory(targetTerritory), deployedArmies(deployedArmies) {}
Deploy::Deploy(const Deploy& deploy):Order(deploy) {
    this->player = deploy.player;
    this->targetTerritory = deploy.targetTerritory;
    this->deployedArmies = deploy.deployedArmies;
}
Deploy& Deploy::operator=(const Deploy& deploy) {
    if (this == &deploy) {
        return *this;
    } else {
        this->player = deploy.player;
        this->targetTerritory = deploy.targetTerritory;
        this->deployedArmies = deploy.deployedArmies;
        return *this;
    }
}
ostream& operator<<(ostream& os, const Deploy& deploy) {
    os << static_cast<const Order&>(deploy);
    os << " - player: " << deploy.player->getName();
    os << " - targetTerritory: " << deploy.targetTerritory->getName();
    os << " - deployedArmies: " << deploy.deployedArmies;

    return os;
}

/**
 * Checks that:
 * 1) the target territory belongs to the player that issued the order
 * 2) the player has the desired amount of armies in their reinforcement pool
 * @return whether the order is valid or not
 */
bool Deploy::validate()  {
    if (player && targetTerritory) {
        if ((player->getName() == *targetTerritory->getPlayerInPossession())
            && (player->getReinforcementPool() >= this->deployedArmies)) {
            return true;
        }
    }

    return false;
}

/**
 * Adds the selected number of player armies for deployment (deployedArmies)
 * to the armies on the target territory.
 */
void Deploy::execute() {
    if (validate()) {
        // add deployed armies to existing armies
        int updatedArmies = *targetTerritory->getArmyCnt() + deployedArmies;
        auto updatedArmiesPtr = make_unique<int>(updatedArmies);
        targetTerritory->setArmyCnt(updatedArmiesPtr);

        // remove deployed armies from the player's reinforcement pool
        player->setReinforcementPool(player->getReinforcementPool() - deployedArmies);
    } else {
        cout << "Invalid deploy order. Could not execute.";
    }
}

// getters and setters
const shared_ptr<Player> &Deploy::getPlayer() const {
    return player;
}

void Deploy::setPlayer(const shared_ptr<Player> &player) {
    Deploy::player = player;
}

const shared_ptr<Territory> &Deploy::getTargetTerritory() const {
    return targetTerritory;
}

void Deploy::setTargetTerritory(const shared_ptr<Territory> &targetTerritory) {
    Deploy::targetTerritory = targetTerritory;
}

int Deploy::getDeployedArmies() const {
    return deployedArmies;
}

void Deploy::setDeployedArmies(int deployedArmies) {
    Deploy::deployedArmies = deployedArmies;
}

// Advance
Advance::Advance():Order() {}
Advance::Advance(const shared_ptr<Player>& player,
                 const shared_ptr<Territory>& sourceTerritory,
                 const shared_ptr<Territory>& targetTerritory,
                 int advanceArmies):
                 player(player),
                 sourceTerritory(sourceTerritory), targetTerritory(targetTerritory),
                 advanceArmies(advanceArmies) {}
Advance::Advance(const Advance& advance):Order(advance) {
    this->player = advance.player;
    this->sourceTerritory = advance.sourceTerritory;
    this->targetTerritory = advance.targetTerritory;
    this->advanceArmies = advance.advanceArmies;
}
Advance& Advance::operator=(const Advance& advance) {
    if (this == &advance) {
        return *this;
    } else {
        this->player = advance.player;
        this->sourceTerritory = advance.sourceTerritory;
        this->targetTerritory = advance.targetTerritory;
        this->advanceArmies = advance.advanceArmies;

        return *this;
    }
}
ostream& operator<<(ostream& os, const Advance& advance) {
    os << static_cast<const Order&>(advance);
    os << " - player: " << advance.player->getName();
    os << " - sourceTerritory: " << advance.sourceTerritory->getName();
    os << " - targetTerritory: " << advance.targetTerritory->getName();
    os << " - advanceArmies: " << advance.advanceArmies;

    return os;
}

/**
 * Checks that:
 * 1) the source territory belongs to the player issuing the order
 * 2) the target territory is adjacent to the source territory
 * 3) the player issuing the order has enough armies to advance
 * @return
 */
bool Advance::validate()  {
    if (*sourceTerritory->getPlayerInPossession() != player->getName()) {
        // source territory doesn't belong to player issuing the order
        return false;
    }
    // TODO: check adjacency
    if (*sourceTerritory->getArmyCnt() < advanceArmies) {
        // player doesn't have enough armies on the source territory
        return false;
    }
    return true;
}

void Advance::execute() {
    // status report
    cout << "Trying to advance " << advanceArmies << " armies from " << this->sourceTerritory->getName()
        << " belonging to " << *this->sourceTerritory->getPlayerInPossession()
        << " to " << this->targetTerritory->getName()
        << " belonging to " << *this->targetTerritory->getPlayerInPossession() << endl;
    if (validate()) {
        // check if the target territory is owned by the player issuing the order
        if (*this->sourceTerritory->getPlayerInPossession() == *this->targetTerritory->getPlayerInPossession()) {
            int sourceArmies = *this->sourceTerritory->getArmyCnt();
            int targetArmies = *this->targetTerritory->getArmyCnt();
            // just move the armies from source to target
            sourceArmies = sourceArmies - advanceArmies;
            targetArmies = targetArmies + advanceArmies;
            auto newSourceArmyPtr = make_unique<int>(sourceArmies);
            auto newTargetArmyPtr = make_unique<int>(targetArmies);
            this->sourceTerritory->setArmyCnt(newSourceArmyPtr);
            this->targetTerritory->setArmyCnt(newTargetArmyPtr);
        } else {
            // the target territory is owned by another player
            attack();
        }

        // report outcome
        cout << "Advance order completed.\nTarget territory status: " << endl << *targetTerritory << endl;
    } else {
        cout << "Invalid advance order. Could not complete." << endl;
    }
}

/**
 * Attack simulation following these rules:
 * 1) each attacking unit has a 60% chance of killing one defending army unit
 * 2) each defending unit has a 70% chance of killing one attacking army unit
 * 3) if all defending armies are eliminated, the attacker captures the territory
 * the surviving attacking units occupy the territory and ownership changes
 * 4) a player receives a card at the end of his turn if they successfully conquered at least one territory
 * during their turn TODO: discuss how to implement this (4)
 */
void Advance::attack() {
    int sourceArmies = *this->sourceTerritory->getArmyCnt();
    int attackingArmies = this->advanceArmies;
    int defendingArmies = *this->targetTerritory->getArmyCnt();

    // move armies out of the source territory
    sourceArmies = sourceArmies - attackingArmies;
    auto newSourceArmyPtr = make_unique<int>(sourceArmies);
    this->sourceTerritory->setArmyCnt(newSourceArmyPtr);

    // set up randomness
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<int> distribution(0,99);

    // decide which army goes first
    bool attackersGoFirst = distribution(generator) < 50;

    // attack loop
    while (attackingArmies > 0 && defendingArmies > 0) {
        if (attackersGoFirst) {
            if (distribution(generator) < 60) {
                // killChance falls within the 60% chance of killing one defending army unit
                defendingArmies--;
            }
            if (defendingArmies != 0) {
                // defenders go now
                if (distribution(generator) < 70) {
                    // killChance falls within the 70% chance of killing one attacking army unit
                    attackingArmies--;
                }
            }
        } else {
            // defenders go first
            if (distribution(generator) < 70) {
                attackingArmies--;
            }
            if (attackingArmies != 0) {
                // attackers go now
                if (distribution(generator) < 60) {
                    defendingArmies--;
                }
            }
        }
    }

    // check who survived
    if (defendingArmies == 0) {
        // defeated defenders, proceed to claim the territory
        this->player->addTerritory(this->targetTerritory);
        // new army count is now the surviving attackers
        auto newArmyCountPtr = make_unique<int>(attackingArmies);
        targetTerritory->setArmyCnt(newArmyCountPtr);
    } else {
        // defenders won, no ownership change, update surviving defending armies
        auto newArmyCountPtr = make_unique<int>(defendingArmies);
        targetTerritory->setArmyCnt(newArmyCountPtr);
    }
}

// getters and setters
const shared_ptr<Player> &Advance::getPlayer() const {
    return player;
}

void Advance::setPlayer(const shared_ptr<Player> &player) {
    Advance::player = player;
}

const shared_ptr<Territory> &Advance::getSourceTerritory() const {
    return sourceTerritory;
}

void Advance::setSourceTerritory(const shared_ptr<Territory> &sourceTerritory) {
    Advance::sourceTerritory = sourceTerritory;
}

const shared_ptr<Territory> &Advance::getTargetTerritory() const {
    return targetTerritory;
}

void Advance::setTargetTerritory(const shared_ptr<Territory> &targetTerritory) {
    Advance::targetTerritory = targetTerritory;
}

int Advance::getAdvanceArmies() const {
    return advanceArmies;
}

void Advance::setAdvanceArmies(int advanceArmies) {
    Advance::advanceArmies = advanceArmies;
}

// Bomb
Bomb::Bomb():Order() {}
Bomb::Bomb(const shared_ptr<Player>& player,
           const shared_ptr<Territory>& targetTerritory):
           player(player), targetTerritory(targetTerritory) {}
Bomb::Bomb(const Bomb& bomb):Order(bomb) {
    this->player = bomb.player;
    this->targetTerritory = bomb.targetTerritory;
}
Bomb& Bomb::operator=(const Bomb& bomb) {
    if (this == &bomb) {
        return *this;
    } else {
        this->player = bomb.player;
        this->targetTerritory = bomb.targetTerritory;

        return *this;
    }
}
ostream& operator<<(ostream& os, const Bomb& bomb) {
    os << static_cast<const Order&>(bomb);
    os << " - player: " << bomb.player->getName();
    os << " - targetTerritory: " << bomb.targetTerritory->getName();

    return os;
}

/**
 * Checks that:
 * 1) the target does not belong to the player issuing the order
 * 2) the target territory is adjacent to one of the territories owned
 * by the player issuing the order
 * TODO: ensure that the bomb order can only be created by playing the bomb card
 * @return whether or not the order is valid
 */
bool Bomb::validate()  {
    if (*this->targetTerritory->getPlayerInPossession() == this->player->getName()) {
        // can't bomb own territory
        return false;
    }

    // TODO: check adjacency to any player-owned territory

    return true;
}

/**
 * Removes half of the armies on the target territory.
 */
void Bomb::execute() {
    // status report
    cout << "Trying to bomb territory:" << endl;
    cout << *this->targetTerritory;
    if (validate()) {
        int targetArmies = *this->targetTerritory->getArmyCnt();
        targetArmies = targetArmies / 2;
        auto newTargetArmiesPtr = make_unique<int>(targetArmies);
        this->targetTerritory->setArmyCnt(newTargetArmiesPtr);

        // update report
        cout << "Successfully bombed territory:" << endl;
        cout << *this->targetTerritory;
    } else {
        cout << "Invalid bomb order. Could not execute." << endl;
    }
}

const shared_ptr<Player> &Bomb::getPlayer() const {
    return player;
}

void Bomb::setPlayer(const shared_ptr<Player> &player) {
    Bomb::player = player;
}

const shared_ptr<Territory> &Bomb::getTargetTerritory() const {
    return targetTerritory;
}

void Bomb::setTargetTerritory(const shared_ptr<Territory> &targetTerritory) {
    Bomb::targetTerritory = targetTerritory;
}

// Blockade
Blockade::Blockade():Order() {}
Blockade::Blockade(const shared_ptr<Player>& player,
                   const shared_ptr<Player>& neutralPlayer,
                   const shared_ptr<Territory>& targetTerritory):
                   player(player), neutralPlayer(neutralPlayer), targetTerritory(targetTerritory) {}
Blockade::Blockade(const Blockade& blockade):Order(blockade) {
    this->player = blockade.player;
    this->neutralPlayer = blockade.neutralPlayer;
    this->targetTerritory = blockade.targetTerritory;
}
Blockade& Blockade::operator=(const Blockade& blockade) {
    if (this == &blockade) {
        return *this;
    } else {
        this->player = blockade.player;
        this->neutralPlayer = blockade.neutralPlayer;
        this->targetTerritory = blockade.targetTerritory;

        return *this;
    }
}
ostream& operator<<(ostream& os, const Blockade& blockade) {
    os << static_cast<const Order&>(blockade);
    os << " - player: " << blockade.player->getName();
    os << " - neutralPlayer: " << blockade.neutralPlayer->getName();
    os << " - targetTerritory: " << blockade.targetTerritory->getName();

    return os;
}

/**
 * Checks that:
 * 1) the target territory belongs to the player issuing the order
 * @return whether the order is valid or not
 */
bool Blockade::validate()  {
    if (*this->targetTerritory->getPlayerInPossession() != this->player->getName()) {
        // target territory doesn't belong to player
        return false;
    }

    return true;
}

/**
 * Doubles the number number of armies on the territory and transfer the ownership
 * to the Neutral player.
 * TODO: ensure the blockade order can only be created by playing the blockade card
 */
void Blockade::execute() {
    if (validate()) {
        // status report
        cout << "Trying to blockade the territory:" << endl;
        cout << *this->targetTerritory;
        // double the number of armies on the territory
        int targetArmies = *this->targetTerritory->getArmyCnt();
        targetArmies = targetArmies * 2;
        auto newTargetArmiesPtr = make_unique<int>(targetArmies);
        this->targetTerritory->setArmyCnt(newTargetArmiesPtr);

        // transfer ownership to the Neutral player
        this->player->removeTerritory(targetTerritory, neutralPlayer);

        // update report
        cout << "Successfully blockaded the territory:" << endl;
        cout << *this->targetTerritory;
    } else {
        cout << "Invalid blockade order. Could not execute." << endl;
    }
}

// getters and setters
const shared_ptr<Player> &Blockade::getPlayer() const {
    return player;
}

void Blockade::setPlayer(const shared_ptr<Player> &player) {
    Blockade::player = player;
}

const shared_ptr<Player> &Blockade::getNeutralPlayer() const {
    return neutralPlayer;
}

void Blockade::setNeutralPlayer(const shared_ptr<Player> &neutralPlayer) {
    Blockade::neutralPlayer = neutralPlayer;
}

const shared_ptr<Territory> &Blockade::getTargetTerritory() const {
    return targetTerritory;
}

void Blockade::setTargetTerritory(const shared_ptr<Territory> &targetTerritory) {
    Blockade::targetTerritory = targetTerritory;
}

// Airlift
Airlift::Airlift():Order() {}
Airlift::Airlift(const shared_ptr<Player>& player,
                 const shared_ptr<Territory>& sourceTerritory,
                 const shared_ptr<Territory>& targetTerritory,
                 int airliftArmies):
                 player(player), sourceTerritory(sourceTerritory),
                 targetTerritory(targetTerritory), airliftArmies(airliftArmies) {}
Airlift::Airlift(const Airlift& airlift):Order(airlift) {
    this->player = airlift.player;
    this->sourceTerritory = airlift.sourceTerritory;
    this->targetTerritory = airlift.targetTerritory;
    this->airliftArmies = airlift.airliftArmies;
}
Airlift& Airlift::operator=(const Airlift& airlift) {
    if (this == &airlift) {
        return *this;
    } else {
        this->player = airlift.player;
        this->sourceTerritory = airlift.sourceTerritory;
        this->targetTerritory = airlift.targetTerritory;
        this->airliftArmies = airlift.airliftArmies;

        return *this;
    }
}
ostream& operator<<(ostream& os, const Airlift& airlift) {
    os << static_cast<const Order&>(airlift);
    os << " - player: " << airlift.player->getName();
    os << " - sourceTerritory: " << airlift.sourceTerritory->getName();
    os << " - targetTerritory: " << airlift.targetTerritory->getName();
    os << " - advanceArmies: " << airlift.airliftArmies;

    return os;
}

/**
 * Check if:
 * 1) the source and target territories belong to the player issuing the order
 * 2) the source territory has the required armies
 * TODO: ensure airlift order can only be created by playing the airlift card
 * @return whether the order is valid or not
 */
bool Airlift::validate()  {
    if (*this->sourceTerritory->getPlayerInPossession() != *this->targetTerritory->getPlayerInPossession()) {
        // source and target territories belong to different players
        return false;
    }

    if (*this->sourceTerritory->getArmyCnt() < this->airliftArmies) {
        // source territory doesn't have enough armies
        return false;
    }

    return true;
}

/**
 * Moves desired armies from a source to target territory without them needing to be adjacent.
 */
void Airlift::execute() {
    // status report
    cout << "Trying to advance " << airliftArmies << " armies from " << this->sourceTerritory->getName()
         << " belonging to " << *this->sourceTerritory->getPlayerInPossession()
         << " to " << this->targetTerritory->getName()
         << " belonging to " << *this->targetTerritory->getPlayerInPossession() << endl;
    if (validate()) {
        // update source and target army counts
        int sourceArmies = *this->sourceTerritory->getArmyCnt();
        int targetArmies = *this->targetTerritory->getArmyCnt();
        sourceArmies = sourceArmies - airliftArmies;
        targetArmies = targetArmies + airliftArmies;

        // create pointers to the new counts
        auto newSourceArmiesPtr = make_unique<int>(sourceArmies);
        auto newTargetArmiesPtr = make_unique<int>(targetArmies);

        // change source and target army count pointers to the new counts
        this->sourceTerritory->setArmyCnt(newSourceArmiesPtr);
        this->targetTerritory->setArmyCnt(newTargetArmiesPtr);

        // report outcome
        cout << "Advance order completed.\nTarget territory status: " << endl << *targetTerritory << endl;
    } else {
        cout << "Invalid airlift order. Could not complete." << endl;
    }
}

// getters and setters
const shared_ptr<Player> &Airlift::getPlayer() const {
    return player;
}

void Airlift::setPlayer(const shared_ptr<Player> &player) {
    Airlift::player = player;
}

const shared_ptr<Territory> &Airlift::getSourceTerritory() const {
    return sourceTerritory;
}

void Airlift::setSourceTerritory(const shared_ptr<Territory> &sourceTerritory) {
    Airlift::sourceTerritory = sourceTerritory;
}

const shared_ptr<Territory> &Airlift::getTargetTerritory() const {
    return targetTerritory;
}

void Airlift::setTargetTerritory(const shared_ptr<Territory> &targetTerritory) {
    Airlift::targetTerritory = targetTerritory;
}

int Airlift::getAirliftArmies() const {
    return airliftArmies;
}

void Airlift::setAirliftArmies(int airliftArmies) {
    Airlift::airliftArmies = airliftArmies;
}

// Negotiate
Negotiate::Negotiate():Order() {}
Negotiate::Negotiate(const Negotiate& negotiate):Order() {} // no members to copy for now
Negotiate& Negotiate::operator=(const Negotiate& negotiate) {
    if (this == &negotiate) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Negotiate& negotiate) {
    os << static_cast<const Order&>(negotiate);
    // no specific member info to return for now

    return os;
}

bool Negotiate::validate()  {
    cout << "negotiate order validated\n";

    return true; // logic to be implemented in later assignments
}

void Negotiate::execute() {
    // logic to be implemented in later assignments
    cout << "negotiate order executed\n";
}

// OrdersList
// default constructor
OrdersList::OrdersList():orderList(make_unique<list<shared_ptr<Order>>>()) {}
// copy constructor
OrdersList::OrdersList(const OrdersList& ordersList) {
    for (const auto& order : *ordersList.orderList) {
        // shallow copy
        this->orderList->push_back(order);
    }
}
// assignment operator
OrdersList& OrdersList::operator=(const OrdersList& ordersList) {
    if (this == &ordersList) {
        return *this;
    } else {
        // make sure we're not iterating over a nullptr
        if (ordersList.orderList) {
            for (const auto& order : *ordersList.orderList) {
                // shallow copy
                this->orderList->push_back(order);
            }
        }

        return *this;
    }
}
// stream insertion operator
ostream& operator<<(ostream& os, const OrdersList& ordersList) {
    // make sure we're not iterating over a nullptr
    if (ordersList.orderList) {
        for (const auto& order : *ordersList.orderList) {
            os << *order << endl;
        }
    } else {
        os << "null\n";
    }

    return os;
}

// utility function to add orders to the orders list
template<typename T>
void OrdersList::add(shared_ptr<T> order) {
    this->orderList->push_back(static_pointer_cast<Order>(order));
}
template<>
void OrdersList::add<Deploy>(shared_ptr<Deploy> deploy) {
    this->orderList->push_back(static_pointer_cast<Order>(deploy));
}

template<>
void OrdersList::add<Advance>(shared_ptr<Advance> advance) {
    this->orderList->push_back(static_pointer_cast<Order>(advance));
}

template<>
void OrdersList::add<Bomb>(shared_ptr<Bomb> bomb) {
    this->orderList->push_back(static_pointer_cast<Order>(bomb));
}

template<>
void OrdersList::add<Blockade>(shared_ptr<Blockade> blockade) {
    this->orderList->push_back(static_pointer_cast<Order>(blockade));
}

template<>
void OrdersList::add<Airlift>(shared_ptr<Airlift> airlift) {
    this->orderList->push_back(static_pointer_cast<Order>(airlift));
}

template<>
void OrdersList::add<Negotiate>(shared_ptr<Negotiate> negotiate) {
    this->orderList->push_back(static_pointer_cast<Order>(negotiate));
}

// move()
/**
 * Finds a given order via its orderID and moves it either up or down in the ordersList
 * @param direction string "up" (previous) or "down" (next)
 * @param orderID int the orderID of the order to be found
 */
void OrdersList::move(const string& direction, int orderID) {
    // find the order in the ordersList using the orderID
    auto orderIterator = find_if(this->orderList->begin(), this->orderList->end(),
                         [orderID](const shared_ptr<Order>& order) { return order->getOrderId() == orderID; });
    // check if found
    if (orderIterator == this->orderList->end()) {
        cout << "couldn't find order with given orderID";
    } else {
        if (direction == "up") {
            // swap the order with the preceding order
            auto previous = prev(orderIterator);
            // check that this is feasible
            if (orderIterator == this->orderList->begin()) {
                cout << "this is already the first order";
            } else {
                // swap
                swap(*orderIterator, *previous);
            }
        } else if (direction == "down") {
            // swap the order with the next order
            auto nextIt = next(orderIterator);
            // check if this is feasible
            if (orderIterator == this->orderList->end()) {
                cout << "this is already the last order";
            } else {
                // swap
                swap(*orderIterator, *nextIt);
            }
        } else {
            cout << "invalid direction" << endl;
        }
    }
}

// remove()
/**
 * Finds an order in the ordersList via its orderID and removes it.
 * @param orderID int orderID of the order to be removed from the list
 */
void OrdersList::remove(int orderID) {
    // find the order via the orderID
    auto orderIterator = find_if(this->orderList->begin(), this->orderList->end(),
                                 [orderID](const shared_ptr<Order>& order) { return order->getOrderId() == orderID; });
    // check that it's found
    if (orderIterator == this->orderList->end()) {
        cout << "order not found with given orderID";
    } else {
        // remove the order
        this->orderList->remove(*orderIterator);
    }
}

// getters and setters
const unique_ptr<list<shared_ptr<Order>>> &OrdersList::getOrderList() const {
    return orderList;
}

void OrdersList::setOrderList(unique_ptr<list<shared_ptr<Order>>> &orderList) {
    OrdersList::orderList = std::move(orderList);
}

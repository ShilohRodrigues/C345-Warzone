#include "Orders.h"

#include <iostream>
#include <list>
#include <algorithm>

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
                 const shared_ptr<Territory>& targetTerritory):
                 player(player), sourceTerritory(sourceTerritory), targetTerritory(targetTerritory) {}
Advance::Advance(const Advance& advance):Order(advance) {
    this->player = advance.player;
    this->sourceTerritory = advance.sourceTerritory;
    this->targetTerritory = advance.targetTerritory;
}
Advance& Advance::operator=(const Advance& advance) {
    if (this == &advance) {
        return *this;
    } else {
        this->player = advance.player;
        this->sourceTerritory = advance.sourceTerritory;
        this->targetTerritory = advance.targetTerritory;

        return *this;
    }
}
ostream& operator<<(ostream& os, const Advance& advance) {
    os << static_cast<const Order&>(advance);
    os << " - player: " << advance.player->getName();
    os << " - sourceTerritory: " << advance.sourceTerritory->getName();
    os << " - targetTerritory: " << advance.targetTerritory->getName();

    return os;
}

bool Advance::validate()  {
    cout << "advance order validated\n";

    return true; // logic to be implemented in later assignments
}

void Advance::execute() {
    // logic to be implemented in later assignments
    cout << "advance order executed\n";
}

// Bomb
Bomb::Bomb():Order() {}
Bomb::Bomb(const Bomb& bomb):Order() {} // no members to copy for now
Bomb& Bomb::operator=(const Bomb& bomb) {
    if (this == &bomb) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Bomb& bomb) {
    os << static_cast<const Order&>(bomb);
    // no specific member info to return for now

    return os;
}

bool Bomb::validate()  {
    cout << "bomb order validated\n";

    return true; // logic to be implemented in later assignments
}

void Bomb::execute() {
    // logic to be implemented in later assignments
    cout << "bomb order executed\n";
}

// Blockade
Blockade::Blockade():Order() {}
Blockade::Blockade(const Blockade& blockade):Order() {} // no members to copy for now
Blockade& Blockade::operator=(const Blockade& blockade) {
    if (this == &blockade) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Blockade& blockade) {
    os << static_cast<const Order&>(blockade);
    // no specific member info to return for now

    return os;
}

bool Blockade::validate()  {
    cout << "blockade order validated\n";

    return true; // logic to be implemented in later assignments
}

void Blockade::execute() {
    // logic to be implemented in later assignments
    cout << "blockade order executed\n";
}

// Airlift
Airlift::Airlift():Order() {}
Airlift::Airlift(const Airlift& airlift):Order() {} // no members to copy for now
Airlift& Airlift::operator=(const Airlift& airlift) {
    if (this == &airlift) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Airlift& airlift) {
    os << static_cast<const Order&>(airlift);
    // no specific member info to return for now

    return os;
}

bool Airlift::validate()  {
    cout << "airlift order validated\n";

    return true; // logic to be implemented in later assignments
}

void Airlift::execute() {
    // logic to be implemented in later assignments
    cout << "airlift order executed\n";
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
        // TODO: check if deep copy?
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
                // TODO: check if deep copy?
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

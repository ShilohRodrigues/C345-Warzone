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
    os << typeid(order).name() << endl;
    os << "orderID: " << order.orderID << endl;

    return os;
}
// validate()
bool Order::validate() { return false; }
// execute()
void Order::execute() {}

// Order subclasses
// validate() for every subclass
// execute() for every subclass

// Deploy
Deploy::Deploy():Order() {}
Deploy::Deploy(const Deploy& deploy):Order() {} // no members to copy for now
Deploy& Deploy::operator=(const Deploy& deploy) {
    if (this == &deploy) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Deploy& deploy) {
    os << static_cast<const Order&>(deploy);
    // no specific member info to return for now

    return os;
}

bool Deploy::validate()  {
    cout << "deploy order validated\n";

    return true; // logic to be implemented in later assignments
}

void Deploy::execute() {
    // logic to be implemented in later assignments
    cout << "deploy order executed\n";
}

// Advance
Advance::Advance():Order() {}
Advance::Advance(const Advance& advance):Order() {} // no members to copy for now
Advance& Advance::operator=(const Advance& advance) {
    if (this == &advance) {
        return *this;
    } else {
        // no members to copy for now
        return *this;
    }
}
ostream& operator<<(ostream& os, const Advance& advance) {
    os << static_cast<const Order&>(advance);
    // no specific member info to return for now

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
        for (const auto& order : *ordersList.orderList) {
            // TODO: check if deep copy?
            this->orderList->push_back(order);
        }

        return *this;
    }
}
// stream insertion operator
ostream& operator<<(ostream& os, const OrdersList& ordersList) {
    for (const auto& order : *ordersList.orderList) {
        os << *order << endl;
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
                         [orderID](const shared_ptr<Order>& order) { return order->orderID == orderID; });
    // check if found
    if (orderIterator == this->orderList->end()) {
        cout << "couldn't find order with given orderID";
    } else {
        // swap the order with the preceding order
        if (direction == "up") {
            auto previous = prev(orderIterator);
            // check that this is feasible
            if (previous == this->orderList->begin()) {
                cout << "this is already the first order";
            } else {
                // swap
                swap(*orderIterator, *previous);
            }
        } else if (direction == "down") {
            // swap the order with the next order
            auto nextIt = next(orderIterator);
            // check if this is feasible
            if (nextIt == this->orderList->end()) {
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
                                 [orderID](const shared_ptr<Order>& order) { return order->orderID == orderID; });
    // check that it's found
    if (orderIterator == this->orderList->end()) {
        cout << "order not found with given orderID";
    } else {
        // remove the order
        this->orderList->remove(*orderIterator);
    }
}
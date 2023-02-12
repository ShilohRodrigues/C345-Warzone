#include "Orders.h"

using namespace std;

void ordersDriver() {
    // create order of every kind
    auto testDeploy = make_shared<Deploy>();
    auto testAdvance = make_shared<Advance>();
    auto testBomb = make_shared<Bomb>();
    auto testBlockade = make_shared<Blockade>();
    auto testAirlift = make_shared<Airlift>();
    auto testNegotiate = make_shared<Negotiate>();

    // create a list of orders
    auto testOrdersList = make_unique<OrdersList>();
    testOrdersList->add(testDeploy);
    testOrdersList->add(testAdvance);
    testOrdersList->add(testBomb);
    testOrdersList->add(testBlockade);
    testOrdersList->add(testAirlift);
    testOrdersList->add(testNegotiate);

    cout << "\n== OrdersList Stream Insertion Operator ==\n" << *testOrdersList << endl;

    for (const auto& order : *testOrdersList->orderList) {
        // every order subclass has validate()
        order->validate();
        // every order subclass has execute()
        order->execute();
    }

    // OrdersList has remove()
    testOrdersList->remove(3); // remove blockade
    cout << "\n== OrdersLost::remove() ==\n" << *testOrdersList << endl;

    //OrdersList has move()
    testOrdersList->move("up", 2); // remove blockade
    cout << "\n== OrdersLost::move() ==\n" << *testOrdersList << endl;
}
#include "Orders.h"

using namespace std;

void ordersDemo1() {
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

    for (const auto& order : *testOrdersList->getOrderList()) {
        // every order subclass has validate()
        order->validate();
        // every order subclass has execute()
        order->execute();
    }

    // OrdersList has remove()
    testOrdersList->remove(3); // remove bomb
    cout << "\n== OrdersLost::remove() ==\n[removing order with orderID 3 (bomb)]\n" << *testOrdersList << endl;

    //OrdersList has move()
    cout << "\n== OrdersLost::move() ==\n[move(\"up\", 2) - swapping advance (2) and deploy (1)]\n";
    testOrdersList->move("up", 2); // swap advance and deploy
    cout << *testOrdersList << endl;
    cout << "[move(\"down\", 5) - swapping airlift (5) and negotiate (6)]\n";
    testOrdersList->move("down", 5);
    cout << *testOrdersList << endl;
}
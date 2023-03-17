#include "Orders.h"
#include "Player.h"
#include "Map.h"

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

void ordersDemo2() {
    // -- DEPLOY TESTS --
    cout << "-- DEPLOY TESTS --" << endl;
    auto testTerritoriesDeploy = make_unique<vector<shared_ptr<Territory>>>();
    auto testDeployTerritory = make_shared<Territory>(0, "deployTerritory", 0, "test", 0);
    testTerritoriesDeploy->push_back(testDeployTerritory);
    cout << "Test deploy territory >> " << *testDeployTerritory << endl;

    // create test player
    auto testPlayerDeploy = make_shared<Player>(3, 3, *testTerritoriesDeploy);
    cout << "Test player (deploy) >> " << *testPlayerDeploy << endl;

    // valid deploy order
    cout << "Deploying 3 armies to the test territory:" << endl;
    auto testDeploy1 =
            make_unique<Deploy>(testPlayerDeploy, testDeployTerritory, 3);
    testDeploy1->execute();
    cout << *testDeployTerritory << endl << *testPlayerDeploy << endl;

    // invalid deploy order
    cout << "Trying to deploy 1 army to the test territory:" << endl;
    auto testDeploy2 =
            make_unique<Deploy>(testPlayerDeploy, testDeployTerritory, 1);
    testDeploy2->execute();

    // -- ADVANCE TESTS --
    cout << "\n\n-- ADVANCE TESTS --" << endl;
    // prepare territories
    auto testAdvanceTerritories = make_unique<vector<shared_ptr<Territory>>>();
    auto testSourceTerritoryAdvance =
            make_shared<Territory>(0, "sourceAdvanceTerritory", 0, "test", 4);
    // one enemy territory
    auto testTargetEnemyAdvance =
            make_shared<Territory>(0, "targetAdvanceEnemyTerritory", 0, "EnemyPlayer", 2);
    // one self-owned territory
    auto testTargetOwnedAdvance =
            make_shared<Territory>(0, "targetAdvanceOwnedTerritory", 0, "test", 2);
    testAdvanceTerritories->push_back(testSourceTerritoryAdvance);
    testAdvanceTerritories->push_back(testTargetOwnedAdvance);

    // prepare player
    auto testPlayerAdvance =
            make_shared<Player>(6, 3, *testAdvanceTerritories);

    // advance to own territory
    cout << "---- Advancing to own territory ----" << endl;
    auto advanceToOwnTerritory = make_unique<Advance>(testPlayerAdvance,
                                                      testSourceTerritoryAdvance,
                                                      testTargetOwnedAdvance,
                                                      1);
    cout << *testPlayerAdvance << endl;
    advanceToOwnTerritory->execute();
    cout << *testPlayerAdvance << endl;

    // advancing to enemy territory
    cout << "---- Advancing to enemy territory ----" << endl;
    auto advanceToEnemyTerritory = make_unique<Advance>(testPlayerAdvance,
                                                      testSourceTerritoryAdvance,
                                                      testTargetEnemyAdvance,
                                                      1);
    cout << *testPlayerAdvance << endl;
    advanceToEnemyTerritory->execute();
    cout << *testPlayerAdvance << endl;
}
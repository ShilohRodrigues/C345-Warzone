#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "LoggingObserver.h"
using namespace std;

void ordersDemo1() {
//    // create order of every kind
//    auto testDeploy = make_shared<Deploy>();
//    auto testAdvance = make_shared<Advance>();
//    auto testBomb = make_shared<Bomb>();
//    auto testBlockade = make_shared<Blockade>();
//    auto testAirlift = make_shared<Airlift>();
//    auto testNegotiate = make_shared<Negotiate>();
//
//    // create a list of orders
//    auto testOrdersList = make_unique<OrdersList>();
//    testOrdersList->add(testDeploy);
//    testOrdersList->add(testAdvance);
//    testOrdersList->add(testBomb);
//    testOrdersList->add(testBlockade);
//    testOrdersList->add(testAirlift);
//    testOrdersList->add(testNegotiate);
//
//    cout << "\n== OrdersList Stream Insertion Operator ==\n" << *testOrdersList << endl;
//
//    for (const auto& order : *testOrdersList->getOrderList()) {
//        // every order subclass has validate()
//        order->validate();
//        // every order subclass has execute()
//        order->execute();
//    }
//
//    // OrdersList has remove()
//    testOrdersList->remove(3); // remove bomb
//    cout << "\n== OrdersLost::remove() ==\n[removing order with orderID 3 (bomb)]\n" << *testOrdersList << endl;
//
//    //OrdersList has move()
//    cout << "\n== OrdersLost::move() ==\n[move(\"up\", 2) - swapping advance (2) and deploy (1)]\n";
//    testOrdersList->move("up", 2); // swap advance and deploy
//    cout << *testOrdersList << endl;
//    cout << "[move(\"down\", 5) - swapping airlift (5) and negotiate (6)]\n";
//    testOrdersList->move("down", 5);
//    cout << *testOrdersList << endl;
}

void ordersDemo2() {
    deployDemo();
    advanceDemo();
    airliftDemo();
    bombDemo();
    blockadeDemo();
    negotiateDemo();
}

void deployDemo() {
    LogObserver gameLogObserver;
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
    testDeploy1->attach(&gameLogObserver);
    testDeploy1->execute();
    cout << *testDeployTerritory << endl << *testPlayerDeploy << endl;

    // invalid deploy order
    cout << "Trying to deploy 1 army to the test territory:" << endl;
    auto testDeploy2 =
            make_unique<Deploy>(testPlayerDeploy, testDeployTerritory, 1);
    testDeploy2->attach(&gameLogObserver);
    testDeploy2->execute();
}

void advanceDemo() {
    // -- ADVANCE TESTS --
    cout << "\n\n-- ADVANCE TESTS --" << endl;
    // prepare territories
    auto testAdvanceTerritories = make_unique<vector<shared_ptr<Territory>>>();
    // one source territory
    auto testSourceTerritoryAdvance =
            make_shared<Territory>(0, "sourceAdvanceTerritory", 0, "test", 5);
    vector<int> adjacentTerritories = {1};
    testSourceTerritoryAdvance->setAdjacentTerritories(make_shared<vector<int>>(adjacentTerritories));
    // one adjacent enemy territory
    auto testAdjacentEnemyAdvance =
            make_shared<Territory>(1, "targetAdvanceAdjacentEnemyTerritory", 0, "EnemyPlayer", 1);
    // one non-adjacent enemy territory
    auto testNonAdjacentEnemyAdvance =
            make_shared<Territory>(2, "targetAdvanceNonAdjacentEnemyTerritory", 0, "EnemyPlayer", 2);
    // one self-owned territory
    auto testTargetOwnedAdvance =
            make_shared<Territory>(3, "targetAdvanceOwnedTerritory", 0, "test", 2);
    testAdvanceTerritories->push_back(testSourceTerritoryAdvance);
    testAdvanceTerritories->push_back(testTargetOwnedAdvance);

    // prepare player
    auto testPlayerAdvance =
            make_shared<Player>(7, 3, *testAdvanceTerritories);

    // advance to own territory
    cout << "---- Advancing to own territory ----" << endl;
    auto advanceToOwnTerritory = make_unique<Advance>(testPlayerAdvance,
                                                      testSourceTerritoryAdvance,
                                                      testTargetOwnedAdvance,
                                                      1);
    cout << *testPlayerAdvance << endl;
    advanceToOwnTerritory->execute();
    cout << *testPlayerAdvance << endl;

    // advancing to adjacent enemy territory
    cout << "---- Advancing to adjacent enemy territory ----" << endl;
    auto advanceToAdjacentEnemyTerritory = make_unique<Advance>(testPlayerAdvance,
                                                                testSourceTerritoryAdvance,
                                                                testAdjacentEnemyAdvance,
                                                                3);
    cout << *testPlayerAdvance << endl;
    advanceToAdjacentEnemyTerritory->execute();
    cout << *testPlayerAdvance << endl;

    // advancing to non-adjacent enemy territory
    cout << "---- Advancing to non-adjacent enemy territory ----" << endl;
    auto advanceToNonAdjacentEnemyTerritory = make_unique<Advance>(testPlayerAdvance,
                                                        testSourceTerritoryAdvance,
                                                        testNonAdjacentEnemyAdvance,
                                                        3);
    advanceToNonAdjacentEnemyTerritory->execute();

    cout << "\nSimulating end of turn . . ." << endl;
    shared_ptr<Deck> deck = make_shared<Deck>();
    deck->MakeDeck();
    testPlayerAdvance->update(deck);
    cout << "Player status: " << endl << *testPlayerAdvance << endl;
}

void airliftDemo() {
    // -- AIRLIFT TESTS --
    cout << "\n\n-- AIRLIFT TESTS --" << endl;
    // prepare territories
    auto testAirliftTerritories = make_unique<vector<shared_ptr<Territory>>>();
    auto testSourceTerritoryAirlift =
            make_shared<Territory>(0, "sourceAirliftTerritory", 0, "test", 10);
    auto testTargetOwnedAirlift =
            make_shared<Territory>(0, "targetAirliftOwned", 0, "test", 2);
    auto testTargetEnemyAirlift =
            make_shared<Territory>(0, "targetAirliftEnemy", 0, "Enemy", 2);
    testAirliftTerritories->push_back(testSourceTerritoryAirlift);
    testAirliftTerritories->push_back(testTargetOwnedAirlift);

    // prepare player
    auto testPlayerAirlift =
            make_shared<Player>(6, 3, *testAirliftTerritories);

    // play airlift card
    cout << "---- Playing Airlift Card ----" << endl;
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testPlayerAirlift->getCardHand()->addCardToHand("Airlift");
    cout << *testPlayerAirlift << endl;
    testPlayerAirlift->playCard(deck, "Airlift");
    cout << *testPlayerAirlift << endl;

    // airlift to own territory
    cout << "---- Airlift to own territory ----" << endl;
    auto airliftToOwnTerritory = make_unique<Airlift>(testPlayerAirlift,
                                                      testSourceTerritoryAirlift,
                                                      testTargetOwnedAirlift,
                                                      3);
    cout << *testPlayerAirlift << endl;
    airliftToOwnTerritory->execute();
    cout << *testPlayerAirlift << endl;

    cout << "---- Airlift to own territory again ----" << endl;
    airliftToOwnTerritory->execute();

    // airlift to enemy territory
    cout << "\n---- Airlift to enemy territory ----" << endl;
    testPlayerAirlift->getCardHand()->addCardToHand("Airlift");
    testPlayerAirlift->playCard(deck, "Airlift");
    auto airliftToEnemyTerritory = make_unique<Airlift>(testPlayerAirlift,
                                                      testSourceTerritoryAirlift,
                                                      testTargetEnemyAirlift,
                                                      1);
    cout << *testPlayerAirlift << endl;
    airliftToEnemyTerritory->execute();

    // airlift without enough armies
    cout << "\n---- Airlift without enough source armies ----" << endl;
    auto airliftShort = make_unique<Airlift>(testPlayerAirlift,
                                                        testSourceTerritoryAirlift,
                                                        testTargetOwnedAirlift,
                                                        3);
    cout << *testPlayerAirlift << endl;
    airliftToOwnTerritory->execute();
}

void bombDemo() {
    // -- BOMB TESTS --
    cout << "\n\n-- BOMB TESTS --" << endl;
    // prepare territories
    auto testBombTerritories = make_unique<vector<shared_ptr<Territory>>>();
    // own territory
    auto testOwnBomb =
            make_shared<Territory>(0, "targetOwnBomb", 0, "test", 2);
    testBombTerritories->push_back(testOwnBomb);
    // adjacent territory
    auto testTargetBombAdjacent =
            make_shared<Territory>(1, "targetEnemyBombAdjacent", 0, "Enemy", 6);
    vector<int> adjacentTerritories = {1};
    testOwnBomb->setAdjacentTerritories(make_shared<vector<int>>(adjacentTerritories));
    // non-adjacent territory
    auto testTargetBombNonAdjacent =
            make_shared<Territory>(2, "targetEnemyBombNonAdjacent", 0, "Enemy", 6);

    // prepare player
    auto testPlayerBomb =
            make_shared<Player>(2, 3, *testBombTerritories);

    // play bomb card
    cout << "---- Playing Bomb Card ----" << endl;
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testPlayerBomb->getCardHand()->addCardToHand("Bomb");
    cout << *testPlayerBomb << endl;
    testPlayerBomb->playCard(deck, "Bomb");
    cout << *testPlayerBomb << endl;

    // bomb adjacent enemy territory
    cout << "---- Bomb adjacent enemy territory (with card) ----" << endl;
    auto bombAdjacentEnemyTerritory = make_unique<Bomb>(testPlayerBomb,
                                                        testTargetBombAdjacent);
    cout << *testPlayerBomb << endl;
    bombAdjacentEnemyTerritory->execute();

    cout << "\n---- Bomb adjacent enemy territory (no card) ----" << endl;
    cout << *testPlayerBomb << endl;
    bombAdjacentEnemyTerritory->execute();

    // bomb non-adjacent enemy territory
    cout << "\n---- Bomb non-adjacent enemy territory (with card) ----" << endl;
    testPlayerBomb->getCardHand()->addCardToHand("Bomb");
    testPlayerBomb->playCard(deck, "Bomb");
    auto bombNonAdjacentEnemyTerritory = make_unique<Bomb>(testPlayerBomb,
                                                        testTargetBombNonAdjacent);
    cout << *testPlayerBomb << endl;
    bombNonAdjacentEnemyTerritory->execute();
    cout << *testPlayerBomb << endl;

    // bomb own territory
    cout << "---- Bomb own territory ----" << endl;
    testPlayerBomb->playCard(deck, "Bomb");
    auto bombOwnTerritory = make_unique<Bomb>(testPlayerBomb,
                                                      testOwnBomb);
    cout << *testPlayerBomb << endl;
    bombOwnTerritory->execute();
    cout << *testPlayerBomb << endl;
}

void blockadeDemo() {
    // -- BLOCKADE TESTS --
    cout << "\n\n-- BLOCKADE TESTS --" << endl;
    // prepare territories
    auto testBlockadeTerritories = make_unique<vector<shared_ptr<Territory>>>();
    auto testOwnBlockade =
            make_shared<Territory>(0, "targetOwnBlockade", 0, "test", 2);
    testBlockadeTerritories->push_back(testOwnBlockade);

    // prepare player
    auto testPlayerBlockade =
            make_shared<Player>(2, 3, *testBlockadeTerritories);
    auto neutralPlayer = make_shared<Player>();

    // blockade own territory
    cout << "---- Blockade own territory (no card) ----" << endl;
    auto blockadeOrder = make_unique<Blockade>(testPlayerBlockade, neutralPlayer,
                                               testOwnBlockade);
    cout << *testPlayerBlockade << endl;
    blockadeOrder->execute();

    // play blockade card
    cout << "\n---- Playing Blockade Card ----" << endl;
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testPlayerBlockade->getCardHand()->addCardToHand("Blockade");
    cout << *testPlayerBlockade << endl;
    testPlayerBlockade->playCard(deck, "Blockade");
    cout << *testPlayerBlockade << endl;

    // blockade own territory
    cout << "---- Blockade own territory (with card) ----" << endl;
    blockadeOrder->execute();
    cout << *testPlayerBlockade << endl;

    // blockade not owned territory
    cout << "---- Blockade not owned territory ----" << endl;
    testPlayerBlockade->getCardHand()->addCardToHand("Blockade");
    testPlayerBlockade->playCard(deck, "Blockade");
    cout << *testPlayerBlockade << endl;
    blockadeOrder->execute(); // blockading again, but now it's owned by the neutral player
}

void negotiateDemo() {
    // -- NEGOTIATE TESTS --
    cout << "\n\n-- NEGOTIATE TESTS --" << endl;

    // prepare territories
    auto testTerritory1 = make_shared<Territory>(0, "testTerritory1", 0, "test", 3);
    auto testTerritory2 = make_shared<Territory>(0, "testTerritory2", 0, "test", 2);

    // prepare player
    auto testPlayerNegotiate1 = make_shared<Player>();
    auto testPlayerNegotiate2 = make_shared<Player>();

    testPlayerNegotiate1->addTerritory(testTerritory1);
    testPlayerNegotiate2->addTerritory(testTerritory2);

    // play diplomacy card
    cout << "---- Playing Diplomacy Card ----" << endl;
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testPlayerNegotiate1->getCardHand()->addCardToHand("Diplomacy");
    cout << *testPlayerNegotiate1 << endl;
    testPlayerNegotiate1->playCard(deck, "Diplomacy");
    cout << *testPlayerNegotiate1 << endl;

    // Negotiate with self
    cout << "---- Negotiate with self ----" << endl;
    auto negotiateSelf = make_unique<Negotiate>(testPlayerNegotiate1, testPlayerNegotiate1);
    cout << *testPlayerNegotiate1 << endl;
    negotiateSelf->execute();

    // Negotiate with other
    cout << "\n---- Negotiate with other ----" << endl;
    testPlayerNegotiate1->playCard(deck, "Diplomacy");
    auto negotiateOther = make_unique<Negotiate>(testPlayerNegotiate1, testPlayerNegotiate2);
    cout << *testPlayerNegotiate1 << endl;
    cout << *testPlayerNegotiate2 << endl;
    negotiateOther->execute();
    cout << *testPlayerNegotiate1 << endl << endl;
    cout << *testPlayerNegotiate2 << endl;

    // Try to attack negotiated player
    cout << "\n---- Attacking negotiated player ----" << endl;
    auto advance = make_unique<Advance>(testPlayerNegotiate1, testTerritory1, testTerritory2, 2);
    advance->execute();
}
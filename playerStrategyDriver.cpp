#include "PlayerStrategies.h"
#include "Map.h"

using namespace std;

void playerStrategyDemo() {
//    aggressiveDemo();
    benevolentDemo();
}

void aggressiveDemo() {
    cout << "-- AGGRESSIVE STRATEGY DEMO --" << endl;
    // make test player
    auto testAggressivePlayer = make_shared<Player>();
    testAggressivePlayer->setReinforcementPool(10);

    // assign strategy
    auto aggressiveStrategy = make_shared<Aggressive>(testAggressivePlayer);
    testAggressivePlayer->setPlayerStrategy(aggressiveStrategy);

    // make territories
    auto testTerritory1 = make_shared<Territory>(1, "testTerritory1", 0, "test", 2);
    auto testTerritory2 = make_shared<Territory>(2, "testTerritory2", 0, "Enemy", 1);
    auto testTerritory3 = make_shared<Territory>(3, "testTerritory3", 0, "Enemy", 1);
    auto testTerritory4 = make_shared<Territory>(4, "testTerritory4", 0, "test", 1);
    auto testTerritory5 = make_shared<Territory>(5, "testTerritory5", 0, "Enemy", 1);
    auto testTerritory6 = make_shared<Territory>(6, "testTerritory6", 0, "Enemy", 1);

    testTerritory1->addAdjacent(testTerritory2);
    testTerritory1->addAdjacent(testTerritory3);
    testTerritory4->addAdjacent(testTerritory5);
    testTerritory4->addAdjacent(testTerritory6);

    // assign territories to player
    testAggressivePlayer->addTerritory(testTerritory1);
    testAggressivePlayer->addTerritory(testTerritory4);

    // simulate turn
    cout << "-- Test Aggressive Player (before): " << endl;
    cout << *testAggressivePlayer << endl;
    testAggressivePlayer->issueOrder();
    cout << "-- Test Aggressive Player (after issuing orders turn 1): " << endl;
    cout << *testAggressivePlayer << endl;
    cout << "We see that the aggressive player has issued a deploy order to its strongest territory, testTerritory1"
            " which has 1 more army than testTerritory4. \nThe aggressive player has also issues two advance orders, "
            "one for each eligible owned territory to a randomly chosen enemy adjacent territory.\n" << endl;
    testAggressivePlayer->getOrdersList()->executeAll();
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testAggressivePlayer->update(deck);

    // simulate another turn
    testAggressivePlayer->issueOrder();
    cout << "\n-- Test Aggressive Player (after issuing orders turn 2): " << endl;
    cout << *testAggressivePlayer << endl;
    cout << "We see that the test aggressive player has succeeded in conquering one or more territories.\n"
            "The player continues to deploy armies to its strongest territory, testTerritory1.\n"
            "Only one advance order is issued at this point, because testTerritory4 has no more armies left to deploy\n"
            "and the newly conquered territory/ies don't have enemy adjacent territories." << endl;
    cout << "\nWe have demonstrated that the aggressive player deploys or advances armies on its strongest territory,\n"
            "then always advances to enemy territories until it cannot do so anymore." << endl;
}

void benevolentDemo() {
    cout << "-- BENEVOLENT STRATEGY DEMO --" << endl;
    // make test player
    auto testBenevolentPlayer = make_shared<Player>();
    testBenevolentPlayer->setReinforcementPool(2);

    // assign strategy
    auto benevolentStrategy = make_shared<Benevolent>(testBenevolentPlayer);
    testBenevolentPlayer->setPlayerStrategy(benevolentStrategy);

    // make territories
    auto testTerritory1 = make_shared<Territory>(1, "testTerritory1", 0, "test", 1);
    auto testTerritory2 = make_shared<Territory>(2, "testTerritory2", 0, "test", 5);
    auto testTerritory3 = make_shared<Territory>(3, "testTerritory3", 0, "test", 1);
    auto testTerritory4 = make_shared<Territory>(4, "testTerritory4", 0, "test", 2);
    auto testTerritory5 = make_shared<Territory>(5, "testTerritory5", 0, "Enemy", 1);
    auto testTerritory6 = make_shared<Territory>(6, "testTerritory6", 0, "Enemy", 1);
    auto testTerritory7 = make_shared<Territory>(7, "testTerritory7", 0, "test", 1);
    auto testTerritory8 = make_shared<Territory>(8, "testTerritory8", 0, "test", 3);

    testTerritory1->addAdjacent(testTerritory2);
    testTerritory1->addAdjacent(testTerritory3);
    testTerritory2->addAdjacent(testTerritory5);
    testTerritory2->addAdjacent(testTerritory6);
    testTerritory3->addAdjacent(testTerritory4);
    testTerritory7->addAdjacent(testTerritory8);

    // assign territories to player
    testBenevolentPlayer->addTerritory(testTerritory1);
    testBenevolentPlayer->addTerritory(testTerritory2);
    testBenevolentPlayer->addTerritory(testTerritory3);
    testBenevolentPlayer->addTerritory(testTerritory4);
    testBenevolentPlayer->addTerritory(testTerritory7);
    testBenevolentPlayer->addTerritory(testTerritory8);

    // simulate turn
    cout << "-- Test Benevolent Player (before): " << endl;
    cout << *testBenevolentPlayer << endl;
    testBenevolentPlayer->issueOrder();
    cout << "-- Test Benevolent Player (after issuing orders turn 1): " << endl;
    cout << *testBenevolentPlayer << endl;
    cout << "We see that the benevolent player has issued two deploy orders to two of its weakest territories (1, 3 —> one army each)."
            "\nWe also see that it has issued one advance order from one of its stronger territories (8 —> 3 armies) to one of its"
            "weaker territories (7 —> 1 army)."
            "\nFinally we note that the benevolent player has not issued any advance orders to enemy territories"
            "\ndespite the enemy territories (5, 6 -> 1 army) being adjacent to the player territory (2 -> 5 armies).\n" << endl;
    testBenevolentPlayer->getOrdersList()->executeAll();
    auto deck = make_shared<Deck>();
    deck->MakeDeck();
    testBenevolentPlayer->update(deck);

    // simulate another turn
    testBenevolentPlayer->issueOrder();
    cout << "\n-- Test Benevolent Player (after issuing orders turn 2): " << endl;
    cout << *testBenevolentPlayer << endl;
    cout << "We see that the benevolent has issued several deploy orders to a subset of its weakest territories\n"
            "until it ran out of reinforcements."
            "\nAgain, we note that the benevolent player has not issued any advance orders towards adjacent enemy territories." << endl;
    cout << "\nWe have demonstrated that the benevolent player deploys or advances on its weakest territories "
            "\nand never advances to enemy territories." << endl;
}

void neutralDemo() {
    auto testNeutralPlayer = make_shared<Player>();
    auto neutralStrategy = make_shared<Neutral>(testNeutralPlayer);
    auto testTerritory = make_shared<Territory>(0, "testTerritory", 0, "test", 0);
    testNeutralPlayer->addTerritory(testTerritory);
    testNeutralPlayer->setPlayerStrategy(neutralStrategy);
    testNeutralPlayer->issueOrder();
    testNeutralPlayer->toAttack();
    testNeutralPlayer->toDefend();
}
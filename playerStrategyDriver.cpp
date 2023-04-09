#include "PlayerStrategies.h"
#include "Map.h"

using namespace std;

void playerStrategyDemo() {
    aggressiveDemo();
}

void aggressiveDemo() {
    // make test player
    auto testAggressivePlayer = make_shared<Player>();
    testAggressivePlayer->setReinforcementPool(10);

    // assign strategy
    auto aggressiveStrategy = make_shared<Aggressive>(testAggressivePlayer);
    testAggressivePlayer->setPlayerStrategy(aggressiveStrategy);

    // make territories
    auto testTerritory1 = make_shared<Territory>(1, "testTerritory", 0, "test", 2);
    auto testTerritory2 = make_shared<Territory>(2, "testTerritory", 0, "Enemy", 1);
    auto testTerritory3 = make_shared<Territory>(3, "testTerritory", 0, "Enemy", 1);
    auto testTerritory4 = make_shared<Territory>(4, "testTerritory", 0, "test", 1);
    auto testTerritory5 = make_shared<Territory>(5, "testTerritory", 0, "Enemy", 1);
    auto testTerritory6 = make_shared<Territory>(6, "testTerritory", 0, "Enemy", 1);

    testTerritory1->getAdjacentTerritoriesPointers()->push_back(testTerritory2);
    testTerritory1->getAdjacentTerritoriesPointers()->push_back(testTerritory3);
    testTerritory4->getAdjacentTerritoriesPointers()->push_back(testTerritory5);
    testTerritory4->getAdjacentTerritoriesPointers()->push_back(testTerritory6);

    // assign territories to player
    testAggressivePlayer->addTerritory(testTerritory1);
    testAggressivePlayer->addTerritory(testTerritory4);

    // simulate turn
    cout << "Orders list before: " << *testAggressivePlayer->getOrdersList();
    testAggressivePlayer->issueOrder();
    cout << "Orders list after: " << *testAggressivePlayer->getOrdersList();
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
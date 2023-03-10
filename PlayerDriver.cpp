#include "Player.h"

using namespace std;

void playerDemo1() {
    // create test territories
    auto testTerritories = make_unique<vector<shared_ptr<Territory>>>();
    for (int i = 0; i < 5; i++) {
        testTerritories->push_back(make_shared<Territory>(i, "testTerritory" + to_string(i), i, "testPlayer", 0));
    }

    // player owns a collection of territories
    cout << "Initializing test Player . . . \n";
    auto testPlayer = make_unique<Player>(*testTerritories);
    cout << "Test player initialized.\n";

    // player owns a hand of warzone cards
    shared_ptr<Deck> deck = make_shared<Deck>();
    deck->MakeDeck();
    for (int i = 0; i < 5; i++)
    {
        testPlayer->getCardHand()->setHandOfCards(deck->draw());
    }

    // show that toDefend() method works
    cout << "\n== Player::toDefend() ==\n";
    auto toDefendList = testPlayer->toDefend();
    for (const auto& t : *toDefendList) {
        cout << *t << endl;
    }

    // show that toAttack() method works
    cout << "\n== Player::toAttack() ==\n";
    auto toAttackList = testPlayer->toAttack();
    for (const auto& t : *toAttackList) {
        cout << *t << endl;
    }

    // show that issueOrder() method works
    cout << "\n== Player::issueOrder() ==\n";
    testPlayer->issueOrder();
    cout << *testPlayer;
}
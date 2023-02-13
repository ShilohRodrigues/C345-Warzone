#include "Player.h"

using namespace std;

// driver creates players + demos features
void playerDriver() {
    auto testTerritories = make_unique<vector<shared_ptr<Territory>>>();
    for (int i = 0; i < 5; i++) {
        testTerritories->push_back(make_shared<Territory>(i, "country", "continent"));
    }

    // player owns a collection of territories + a hand of warzone cards
    cout << "Initializing test Player . . . \n";
    auto testPlayer = make_unique<Player>();
    cout << "Test player initialized.\n";

    // show that toDefend() method works
    cout << "\n== Player::toDefend() ==\n";
    testPlayer->toDefend();

    // show that toAttack() method works
    cout << "\n== Player::toAttack() ==\n";
    testPlayer->toAttack();

    // show that issueOrder() method works
    cout << "\n== Player::issueOrder() ==\n";
    testPlayer->issueOrder();
    cout << *testPlayer;
}
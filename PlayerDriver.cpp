#include "Player.h"

using namespace std;

// driver creates players + demos features
int main() {
    auto testTerritories = make_unique<vector<Territory*>>();
    for (int i = 0; i < 5; i++) {
        testTerritories->push_back(new Territory());
    }

    // initialize test player
    cout << "Initializing test Player . . . \n";
    auto testPlayer = new Player(*testTerritories);
    cout << "Test player initialized.\n";

    // show that the stream insertion operator works
    cout << "\n== Player Stream Insertion ==\n" << *testPlayer << endl;

    // show that the copy constructor works
    auto testPlayerCopied = new Player(*testPlayer);
    cout << "\n== Player Copy Constructor ==\n" << *testPlayerCopied << endl;

    // show that the assignment operator works
    Player* testPlayerAssigned = testPlayer;
    cout << "\n== Player Assignment Operator ==\n" << *testPlayerAssigned << endl;

    // show that toDefend() method works
    cout << "\n== Player::toDefend() ==\n";
//    testPlayer->toDefend();

    // show that toAttack() method works
    cout << "\n== Player::toAttack() ==\n";
//    testPlayer->toAttack();

    // show that issueOrder() method works
    cout << "\n== Player::issueOrder() ==\n";
//    testPlayer->issueOrder();
    cout << *testPlayer;


    // delete test territories when done testing
    for (Territory *territory : *testTerritories) {
        delete territory;
    }
}
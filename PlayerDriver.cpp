#include "Player.h"
#include <iostream>

// driver creates players + demos features
int main() {
    std::vector<Territory*> testTerritories;
    for (int i = 0; i < 5; i++) {
        testTerritories.push_back(*new Territory*());
    }

    // initialize test player
    Player* testPlayer = new Player(testTerritories);

    // show that the stream insertion operator works
    cout << *testPlayer;

    // show that the copy constructor works

    // show that the assignment operator works


    // show that toDefend() method works
//    testPlayer->toDefend();

    // show that toAttack() method works
//    testPlayer->toAttack();

    // show that issueOrder() method works
//    testPlayer->issueOrder();


}
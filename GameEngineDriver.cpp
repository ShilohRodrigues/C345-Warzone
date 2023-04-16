#include <iostream>
#include "GameEngine.h"

using namespace std;

void mainGameLoop(GameEngine* game) {

    bool gameEnded = false;

    while (!gameEnded) {

        game->reinforcementPhase();
        game->issueOrdersPhase();
        game->executeOrdersPhase();

        // need a condition from other class to determine if the game has ended


        if (gameEnded) {
            cout << "Game ended, Thank you for playing!" << endl;
        }
    }
}

void gameEngineDemo1() {

    //Create game object
    GameEngine* game = new GameEngine();
    
    cout << "Welcome to Warzone" << endl;
    
    mainGameLoop(game);

    delete game;

}
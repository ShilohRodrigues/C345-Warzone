#include <iostream>

#include "Cards.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "CommandProcessing.h"

using namespace std;

int main(int argc, char *argv[]) {

     //Part 1 Demo
    GameEngine *game = new GameEngine();
    //Check if reading from file or from command line
    if (string(argv[1]).find("-file")!= std::string::npos) {
        CommandProcessingDriverDemo(*game, string(argv[1]).substr(5));
    }       
    else if (string(argv[1]) == "-console") {
        CommandProcessingDriverDemo(*game, "");
    }
    delete game;

    return 0;
}
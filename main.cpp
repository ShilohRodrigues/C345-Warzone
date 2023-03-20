#include <iostream>

#include "Cards.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "CommandProcessing.h"

using namespace std;

int main() {
//    cardDemo1();
//    gameEngineDemo1();
//    ordersDemo1();
//    playerDemo1();
//    mapDemo1();

//  ordersDemo2();

  GameEngine *game = new GameEngine();
  game->startupPhase();
  delete game;

   return 0;

}
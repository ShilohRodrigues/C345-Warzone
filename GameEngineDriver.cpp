#include <iostream>
#include "GameEngine.h"

using namespace std;

int main() {

  //Create game object
  Game *game = new Game();

  cout << "Welcome to Warzone" << endl << endl;

  //Main game loop
  while(true) {

    cout << *game << endl << endl; //Print current game state
    cout << "Enter a command to continue: ";

    //Get entered command, check return status, 1 for error, 2 for game ended
    string input = ""; 
    getline(cin, input);

    if (input == "quit") break;
    int status = game->nextState(input);
    if (status == 1) cout << "Invalid command entered: " << input << endl << endl;
    if (status == 2) {
      cout << "Game ended, Thank you for playing!" << endl;
      break;
    } 

  }
  
  delete game;

} 
#include <iostream>
#include "GameEngine.h"

using namespace std;

int main() {

  //Create game object
  Game *game = new Game();

  cout << "Welcome to Warzone" << endl << endl;

  //Game loop
  while(true) {

    cout << *game << endl << endl;
    cout << "Enter a command to continue: ";

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
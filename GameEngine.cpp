#include <iostream>
#include "GameEngine.h"

using namespace std;

//Game constructor, initializes the state to the starting state
Game::Game() {
  state = new StartState();
}
//Initializes the state to the entered state
Game::Game(State *newState) {
  state = newState;
}
int Game::nextState(string cmd) {
  return state->next(this, cmd);
}
//Insertion Stream
ostream& operator<<(ostream &strm, const Game &g) {
  //Loop through available commands to print them
  string cmds = "";
  for(string cmd : g.state->getCommands()) {
    cmds += cmd + ", ";
  }
  cmds = cmds.substr(0, cmds.size()-2); //Remove trailing comma
  return strm << "Current state: " << *g.state << endl << "Available commands: " << cmds;
}

//State class insertion stream
ostream &operator<<(ostream &strm, State const &s) { 
  return s.output(strm);
}

//Start State class implementations
void StartState::action() {

}
int StartState::next(Game *game, string cmd) {
  if (cmd == "loadmap") {
    game->setState(new MapLoadedState());
    return 0; //Return 0 for success
  }
  else {
    return 1; //Return 1 for error
  }
}

//Map Loaded State class implementations
void MapLoadedState::action() {

}
int MapLoadedState::next(Game *game, string cmd) {
  if (cmd == "loadmap") {
    return 0;
  }
  else if (cmd == "validatemap") {
    game->setState(new MapValidatedState());
    return 0;
  }
  else {
    return 1;
  }
}

//Map Validated State class implementations
void MapValidatedState::action() {

}
int MapValidatedState::next(Game *game, string cmd) {
  if (cmd == "addplayer") {
    game->setState(new PlayersAddedState());
    return 0;
  }
  else {
    return 1;
  }
}

//Players added State class implementations
void PlayersAddedState::action() {

}
int PlayersAddedState::next(Game *game, string cmd) {
  if (cmd == "addplayer") {
    return 0;
  }
  else if (cmd == "assigncountries") {
    game->setState(new AssignReinforcementState());
    return 0;
  }
  else {
    return 1;
  }
}

//Assign Reinforcements State class implementations
void AssignReinforcementState::action() {

}
int AssignReinforcementState::next(Game *game, string cmd) {
  if (cmd == "issueorder") {
    game->setState(new IssueOrdersState());
    return 0;
  }
  else {
    return 1;
  }
}

//Issue Orders State class implementations
void IssueOrdersState::action() {

}
int IssueOrdersState::next(Game *game, string cmd) {
  if (cmd == "issueorder") {
    return 0;
  }
  else if (cmd == "endissueorders") {
    game->setState(new ExecuteOrdersState());
    return 0;
  }
  else {
    return 1;
  }
}

//Execute Orders State class implementations
void ExecuteOrdersState::action() {

}
int ExecuteOrdersState::next(Game *game, string cmd) {
  if (cmd == "execorder") {
    return 0;
  }
  else if (cmd == "endexecorders") {
    game->setState(new AssignReinforcementState());
    return 0;
  }
  else if (cmd == "win") {
    game->setState(new WinState());
    return 0;
  }
  else {
    return 1;
  }
}

//Win State class implementations
void WinState::action() {

}
int WinState::next(Game *game, string cmd) {
  if (cmd == "play") {
    game->setState(new StartState());
    return 0;
  }
  else if (cmd == "end") {
    return 2; //Return 2 for end of game
  }
  else {
    return 1;
  }
}
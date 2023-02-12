#include <iostream>
#include <memory>
#include "GameEngine.h"

using namespace std;

///////////////// Game Class Implementations //////////////////////////
//Game constructor, initializes the state to the starting state
GameEngine::GameEngine() {
  state = shared_ptr<State>(new StartState()); //Shared pointed, no need to delete
}
//Parameterized Constructor
GameEngine::GameEngine(shared_ptr<State> newState) {
  this->state = newState;
}
//Copy Constructor
GameEngine::GameEngine(GameEngine &game) {
  state = game.state;
}
//Assignment Operator
GameEngine& GameEngine::operator=(const GameEngine& game) {
  if (this == &game) return *this;
  this->state = game.state;
  return *this;
}
//Insertion Stream
ostream& operator<<(ostream &strm, const GameEngine &g) {
  //Loop through available commands to print them
  string cmds = "";
  for(string cmd : g.state->getCommands()) {
    cmds += cmd + ", ";
  }
  cmds = cmds.substr(0, cmds.size()-2); //Remove trailing comma
  return strm << "Current state: " << *g.state << endl << "Available commands: " << cmds;
}
//Attempt to go to the next state with the entered command
int GameEngine::nextState(string cmd) {
  return state->next(this, cmd);
}
//State Getter
shared_ptr<State> GameEngine::getState() { 
  return this->state; 
}
//State Setter
void GameEngine::setState(shared_ptr<State> newState) { 
  this->state = newState; 
}
//Destructor 
GameEngine::~GameEngine() { /*Using smart pointers*/ }

///////////////// State Class Implementations //////////////////////////
//State class insertion stream
ostream &operator<<(ostream &strm, State const &s) { 
  return s.output(strm);
}

///////////////// StartState Class Implementations //////////////////////////
void StartState::action() {

}
int StartState::next(GameEngine *game, string cmd) {
  if (cmd == "loadmap") {
    game->setState(shared_ptr<State>(new MapLoadedState()));
    return 0; //Return 0 for success
  }
  else {
    return 1; //Return 1 for error
  }
}
//Command Getter
vector<string> StartState::getCommands(){ 
  return commands; 
}

////////////////// Map Loaded State class implementations //////////////////
void MapLoadedState::action() {

}
int MapLoadedState::next(GameEngine *game, string cmd) {
  if (cmd == "loadmap") {
    return 0;
  }
  else if (cmd == "validatemap") {
    game->setState(shared_ptr<State>(new MapValidatedState()));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> MapLoadedState::getCommands(){ 
  return commands; 
}

////////////// Map Validated State class implementations ///////////////////////
void MapValidatedState::action() {

}
int MapValidatedState::next(GameEngine *game, string cmd) {
  if (cmd == "addplayer") {
    game->setState(shared_ptr<State>(new PlayersAddedState()));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> MapValidatedState::getCommands(){ 
  return commands; 
}

///////////// Players added State class implementations ///////////////////////////
void PlayersAddedState::action() {

}
int PlayersAddedState::next(GameEngine *game, string cmd) {
  if (cmd == "addplayer") {
    return 0;
  }
  else if (cmd == "assigncountries") {
    game->setState(shared_ptr<State>(new AssignReinforcementState()));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> PlayersAddedState::getCommands(){ 
  return commands; 
}

////////////// Assign Reinforcements State class implementations //////////////////////
void AssignReinforcementState::action() {

}
int AssignReinforcementState::next(GameEngine *game, string cmd) {
  if (cmd == "issueorder") {
    game->setState(shared_ptr<State>(new IssueOrdersState));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> AssignReinforcementState::getCommands(){ 
  return commands; 
}

//////////////// Issue Orders State class implementations //////////////////////////
void IssueOrdersState::action() {

}
int IssueOrdersState::next(GameEngine *game, string cmd) {
  if (cmd == "issueorder") {
    return 0;
  }
  else if (cmd == "endissueorders") {
    game->setState(shared_ptr<State>(new ExecuteOrdersState()));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> IssueOrdersState::getCommands(){ 
  return commands; 
}

/////////////// Execute Orders State class implementations /////////////////////
void ExecuteOrdersState::action() {

}
int ExecuteOrdersState::next(GameEngine *game, string cmd) {
  if (cmd == "execorder") {
    return 0;
  }
  else if (cmd == "endexecorders") {
    game->setState(shared_ptr<State>(new AssignReinforcementState()));
    return 0;
  }
  else if (cmd == "win") {
    game->setState(shared_ptr<State>(new WinState()));
    return 0;
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> ExecuteOrdersState::getCommands(){ 
  return commands; 
}

//////////////////////// Win State class implementations ///////////////////////////
void WinState::action() {

}
int WinState::next(GameEngine *game, string cmd) {
  if (cmd == "play") {
    game->setState(shared_ptr<State>(new StartState()));
    return 0;
  }
  else if (cmd == "end") {
    return 2; //Return 2 for end of game
  }
  else {
    return 1;
  }
}
//Command Getter
vector<string> WinState::getCommands(){ 
  return commands; 
}
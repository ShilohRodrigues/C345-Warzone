#ifndef GAME_ENGINE //include guard
#define GAME_ENGINE

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Map.h"
#include "Player.h"
using namespace std;

class State;
class GameEngine;

//Game class, tracks the state of the game and controls going to the next and previous states
class GameEngine{
  public:
    GameEngine();
    ~GameEngine();
    GameEngine(shared_ptr<State> newState);
    GameEngine& operator=(const GameEngine& game);
    GameEngine(GameEngine &game);
    friend ostream& operator<<(ostream& strm, const GameEngine& g);

    void startupPhase();
    int nextState(string cmd);
    shared_ptr<State> getState();
    void setState(shared_ptr<State> newState);

    void setMap(Map m);
    shared_ptr<Map> getMap();

    void addPlayer(Player &p);
    int playerCount();
    string getPlayerName(int i);


    //part 5

    
  private:
    shared_ptr<State> state;  //Tracks the state of the game  
    shared_ptr<Map> map;
    vector<Player> players;
};

//State Interface, all states must inherit this class and implement all its methods
class State {
  public:
    virtual ostream &output(ostream &strm) const = 0;
    friend ostream &operator<<(ostream &strm, State const &s);
    virtual void action() = 0;
    virtual int next(GameEngine *game, string cmd) = 0;
    virtual vector<string> getCommands() = 0;
};

//Different states that implement the abstract state class
class StartState: public State {
  public:
    StartState();
    ~StartState();
    StartState& operator=(const StartState& state);
    StartState(StartState &state);
    ostream &output(ostream &strm) const override { return strm << "start"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"loadmap <filename>"};
};
class MapLoadedState: public State {
  public:
    MapLoadedState();
    ~MapLoadedState();
    MapLoadedState& operator=(const MapLoadedState& state);
    MapLoadedState(MapLoadedState &state);
    ostream &output(ostream &strm) const override { return strm << "map loaded"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"loadmap <filename>", "validatemap"};
};
class MapValidatedState: public State {
  public:
    MapValidatedState();
    ~MapValidatedState();
    MapValidatedState& operator=(const MapValidatedState& state);
    MapValidatedState(MapValidatedState &state);
    ostream &output(ostream &strm) const override { return strm << "map validated"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"addplayer"};
};
class PlayersAddedState: public State {
  public:
    PlayersAddedState();
    ~PlayersAddedState();
    PlayersAddedState& operator=(const PlayersAddedState& state);
    PlayersAddedState(PlayersAddedState &state);
    ostream &output(ostream &strm) const override { return strm << "players added"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"addplayer", "gamestart"};
};
class AssignReinforcementState: public State {
  public:
    AssignReinforcementState();
    ~AssignReinforcementState();
    AssignReinforcementState& operator=(const AssignReinforcementState& state);
    AssignReinforcementState(AssignReinforcementState &state);
    ostream &output(ostream &strm) const override { return strm << "assign reinforcements"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"issueorder"};
};
class IssueOrdersState: public State {
  public:
    IssueOrdersState();
    ~IssueOrdersState();
    IssueOrdersState& operator=(const IssueOrdersState& state);
    IssueOrdersState(IssueOrdersState &state);
    ostream &output(ostream &strm) const override { return strm << "issue orders"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"issueorder", "endissueorders"};
};
class ExecuteOrdersState: public State {
  public:
    ExecuteOrdersState();
    ~ExecuteOrdersState();
    ExecuteOrdersState& operator=(const ExecuteOrdersState& state);
    ExecuteOrdersState(ExecuteOrdersState &state);
    ostream &output(ostream &strm) const override { return strm << "execute orders"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"execorder", "endexecorder", "win"};
};
class WinState: public State {
  public:
    WinState();
    ~WinState();
    WinState& operator=(const WinState& state);
    WinState(WinState &state);
    ostream &output(ostream &strm) const override { return strm << "Win"; }

    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;

  private:
    vector<string> commands{"end", "play"};
};

void gameEngineDemo1();

#endif // GAME_ENGINE
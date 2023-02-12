#ifndef GAME_ENGINE //include guard
#define GAME_ENGINE

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class State;
class GameEngine;

//Game class, tracks the state of the game and controls going to the next and previous states
class GameEngine {
  public:
    GameEngine();
    ~GameEngine();
    GameEngine(shared_ptr<State> newState);
    GameEngine& operator=(const GameEngine& game);
    GameEngine(GameEngine &game);
    friend ostream& operator<<(ostream& strm, const GameEngine& g);

    int nextState(string cmd);
    shared_ptr<State> getState();
    void setState(shared_ptr<State> newState);
    
  private:
    shared_ptr<State> state;  //Tracks the state of the game  
};

//State Interface, all states must inherit this class and implement all its methods
class State {
  public:
    virtual void action() = 0;
    virtual int next(GameEngine *game, string cmd) = 0;
    virtual vector<string> getCommands() = 0;
    virtual ostream &output(ostream &strm) const = 0;
    friend ostream &operator<<(ostream &strm, State const &s);
};

//Different states that implement the abstract state class
class StartState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "start"; }

  private:
    vector<string> commands{"loadmap"};
};
class MapLoadedState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "map loaded"; }

  private:
    vector<string> commands{"loadmap", "validatemap"};
};
class MapValidatedState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "map validated"; }

  private:
    vector<string> commands{"addplayer"};
};
class PlayersAddedState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "players added"; }

  private:
    vector<string> commands{"addplayer", "assigncountries"};
};
class AssignReinforcementState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "assign reinforcements"; }

  private:
    vector<string> commands{"issueorder"};
};
class IssueOrdersState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "issue orders"; }

  private:
    vector<string> commands{"issueorder", "endissueorders"};
};
class ExecuteOrdersState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "execute orders"; }

  private:
    vector<string> commands{"execorder", "endexecorder", "win"};
};
class WinState: public State {
  public:
    virtual void action() override;
    virtual int next(GameEngine *game, string cmd) override;
    virtual vector<string> getCommands() override;
    ostream &output(ostream &strm) const override { return strm << "Win"; }

  private:
    vector<string> commands{"end", "play"};
};

#endif // GAME_ENGINE
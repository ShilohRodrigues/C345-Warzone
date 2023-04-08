#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Map.h"

using namespace std;

class Player;

class PlayerStrategy {
public:
    PlayerStrategy(Player& player);

    virtual void issueOrder() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toAttack() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toDefend() = 0;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(shared_ptr<Player> &player);

protected:
    shared_ptr<Player> player;
};

class Human: public PlayerStrategy {
public:
    Human(Player& player);
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Aggressive: public PlayerStrategy {
public:
    Aggressive(Player& player);
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Benevolent: public PlayerStrategy {
public:
    Benevolent(Player& player);
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Neutral: public PlayerStrategy {
public:
    Neutral(Player& player);
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Cheater: public PlayerStrategy {
public:
    Cheater(Player& player);
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

void playerStrategyDemo();

#endif // PLAYERSTRATEGIES_H
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
    virtual void issueOrder() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toAttack() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toDefend() = 0;

protected:
    unique_ptr<Player> player;
};

class Human: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Aggressive: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Benevolent: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Neutral: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

class Cheater: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

#endif // PLAYERSTRATEGIES_H
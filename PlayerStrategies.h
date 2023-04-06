#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include <vector>
#include <memory>
#include "Map.h"

using namespace std;

class PlayerStrategy {
public:
    virtual void issueOrder() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toAttack() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toDefend() = 0;
};

class Human: public PlayerStrategy {
public:
    void issueOrder();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
};

#endif // PLAYERSTRATEGIES_H
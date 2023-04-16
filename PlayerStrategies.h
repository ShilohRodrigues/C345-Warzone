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
    PlayerStrategy(shared_ptr<Player> player);
    PlayerStrategy(const PlayerStrategy& playerStrategy);
    PlayerStrategy& operator=(const PlayerStrategy& playerStrategy);
    friend ostream& operator<<(ostream& os, const PlayerStrategy& playerStrategy);

    virtual void issueOrder() = 0;
    virtual unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> getToAttackMap();
    virtual unique_ptr<vector<shared_ptr<Territory>>> toAttack() = 0;
    virtual unique_ptr<vector<shared_ptr<Territory>>> toDefend() = 0;

    const shared_ptr<Player> &getPlayer() const;
    void setPlayer(shared_ptr<Player> &player);

    const string &getStrategyName() const;
    void setStrategyName(const string &strategyName);

protected:
    shared_ptr<Player> player;
    string strategyName;
};

class Human: public PlayerStrategy {
public:
    Human(shared_ptr<Player> player);
    Human(const Human& human);
    Human& operator=(const Human& human);
    friend ostream& operator<<(ostream& os, const Human& human);

    void issueOrder() override;
    unique_ptr<vector<shared_ptr<Territory>>> toAttack() override;
    unique_ptr<vector<shared_ptr<Territory>>> toDefend() override;
};

class Aggressive: public PlayerStrategy {
public:
    Aggressive(shared_ptr<Player> player);
    Aggressive(const Aggressive& aggressive);
    Aggressive& operator=(const Aggressive& aggressive);
    friend ostream& operator<<(ostream& os, const Aggressive& aggressive);

    void issueOrder() override;
    unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> getToAttackMap() override;
    unique_ptr<vector<shared_ptr<Territory>>> toAttack() override;
    unique_ptr<vector<shared_ptr<Territory>>> toDefend() override;
    shared_ptr<Territory> getStrongestTerritory();
};

class Benevolent: public PlayerStrategy {
public:
    Benevolent(shared_ptr<Player> player);
    Benevolent(const Benevolent& benevolent);
    Benevolent& operator=(const Benevolent& benevolent);
    friend ostream& operator<<(ostream& os, const Benevolent& benevolent);

    void issueOrder() override;
    unique_ptr<vector<shared_ptr<Territory>>> toAttack() override;
    unique_ptr<vector<shared_ptr<Territory>>> toDefend() override;
};

class Neutral: public PlayerStrategy {
public:
    Neutral(shared_ptr<Player> player);
    Neutral(const Neutral& neutral);
    Neutral& operator=(const Neutral& neutral);
    friend ostream& operator<<(ostream& os, const Neutral& neutral);

    void issueOrder() override;
    unique_ptr<vector<shared_ptr<Territory>>> toAttack() override;
    unique_ptr<vector<shared_ptr<Territory>>> toDefend() override;
};

class Cheater: public PlayerStrategy {
public:
    Cheater(shared_ptr<Player> player);
    Cheater(const Cheater& cheater);
    Cheater& operator=(const Cheater& cheater);
    friend ostream& operator<<(ostream& os, const Cheater& cheater);

    void issueOrder() override;
    unique_ptr<vector<shared_ptr<Territory>>> toAttack() override;
    unique_ptr<vector<shared_ptr<Territory>>> toDefend() override;
};

void playerStrategyDemo();
void aggressiveDemo();
void benevolentDemo();
void neutralDemo();

#endif // PLAYERSTRATEGIES_H
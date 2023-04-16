#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <memory>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "GameEngine.h"
#include "PlayerStrategies.h"

using namespace std;
class GameEngine;
class OrdersList;
class PlayerStrategy;

class Player {
public:
    // default constructor
    Player();
    explicit Player(const vector<shared_ptr<Territory>>& territories);
    Player(int armyCount, int reinforcementPool, const vector<shared_ptr<Territory>>& territories);
    // copy constructor
    Player(const Player& player);
    // assignment operator
    Player& operator=(const Player& player);
    // stream insertion operator (friend)
    friend ostream& operator<<(ostream& os, const Player& player);
    // destructor
    ~Player();

    // required methods
    unique_ptr<vector<shared_ptr<Territory>>> toDefend();
    unique_ptr<vector<shared_ptr<Territory>>> toAttack();
    void issueOrder();

    // extra methods
    void addTerritory(const shared_ptr<Territory>& territory);
    void removeTerritory(const shared_ptr<Territory>& territory);
    void removeTerritory(const shared_ptr<Territory>& territory, const shared_ptr<Player>& newOwner);
    void updateTerritories();

    void addNegotiatedPlayer(const shared_ptr<Player>& player);
    void clearNegotiatedPlayers();
    bool isInNegotiatedPlayers(string playerName);

    int updateArmyCount();

    void drawIfHasConquered(const shared_ptr<Deck>& deck);
    bool hasPlayedCard(const string& cardType);
    bool hasCardInHand(const string& cardType);
    void playCard(const shared_ptr<Deck>& deck, const string& cardType);

    bool wasAttacked();
    
    void update(const shared_ptr<Deck>& deck);

    // getters and setters
    string getName();

    int getArmyCount() const;
    void setArmyCount(int armyCount);

    int getReinforcementPool() const;
    void setReinforcementPool(int reinforcementPool);

    const unique_ptr<Hand> &getCardHand() const;
    void setCardHand(unique_ptr<Hand> &cardHand);

    const unique_ptr<vector<shared_ptr<Territory>>> &getTerritories() const;
    void setTerritories(unique_ptr<vector<shared_ptr<Territory>>> &territories);

    const shared_ptr<OrdersList> &getOrdersList() const;
    void setOrdersList(shared_ptr<OrdersList> &ordersList);

    const unique_ptr<vector<shared_ptr<Player>>> &getNegotiatedPlayers() const;
    void setNegotiatedPlayers(const unique_ptr<vector<shared_ptr<Player>>> &negotiatedPlayers);

    bool getHasConqueredTerritory() const;
    void setHasConqueredTerritory(bool hasConqueredTerritory);

    const shared_ptr<PlayerStrategy> &getPlayerStrategy();

    template <typename T>
    void setPlayerStrategy(shared_ptr<T> &playerStrategy);
    void setPlayerStrategy1(shared_ptr<PlayerStrategy> &ps);

    bool hasOrders() const;
    //part 3
    Player(std::string& playerName, GameEngine* gameEngine);
    shared_ptr<Territory> getTerritoryByID(int territoryID) const;

private:
    static int nextID;
    string name;
    int armyCount; // total army count available to the player
    int reinforcementPool; // armies the player can use every turn, decreases as the player uses them, replenishes later
    bool hasConqueredTerritory; // true if the player has conquered a territory anytime during the current turn
    // player owns a hand of Warzone cards
    unique_ptr<Hand> cardHand;
    // player owns collection of territories
    unique_ptr<vector<shared_ptr<Territory>>> territories;
    // player has list of orders
    shared_ptr<OrdersList> ordersList;
    // for the negotiation order
    unique_ptr<vector<shared_ptr<Player>>> negotiatedPlayers;

    //part 3
    GameEngine* gameEngine;
    GameEngine* getGameEngine();

    shared_ptr<PlayerStrategy> playerStrategy;
};

class NeutralPlayer : public Player {
public:
    NeutralPlayer();
};

void playerDemo1();

#endif // PLAYER_H

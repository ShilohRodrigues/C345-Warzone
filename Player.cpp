#include "Player.h"
#include <algorithm>
#include "GameEngine.h"

using namespace std;

int Player::nextID = 0;

Player::Player(std::string& playerName, GameEngine* gameEngine)
    : name(playerName), gameEngine(gameEngine) {
}

GameEngine* Player::getGameEngine(){
    return gameEngine;
}

// default constructor
Player::Player():
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>()),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()),
    hasConqueredTerritory(false) {}

// parameterized constructors (for testing)
Player::Player(const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(3),
    reinforcementPool(3),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()),
    hasConqueredTerritory(false) {
    setTerritories(this->territories);
}

Player::Player(int armyCount, int reinforcementPool, const vector<shared_ptr<Territory>>& territories):
    name("Player" + to_string(++nextID)),
    armyCount(armyCount),
    reinforcementPool(reinforcementPool),
    territories(make_unique<vector<shared_ptr<Territory>>>(territories)),
    cardHand(make_unique<Hand>()),
    ordersList(make_unique<OrdersList>()),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()),
    hasConqueredTerritory(false) {
    setTerritories(this->territories);
}

// copy constructor
Player::Player(const Player& player):
    name(player.name),
    armyCount(player.armyCount),
    reinforcementPool(player.reinforcementPool),
    territories(make_unique<vector<shared_ptr<Territory>>>()),
    cardHand(make_unique<Hand>(*player.cardHand)),
    ordersList(make_unique<OrdersList>(*player.ordersList)),
    negotiatedPlayers(make_unique<vector<shared_ptr<Player>>>()),
    hasConqueredTerritory(player.hasConqueredTerritory) {
    for (const auto& t: *player.territories) {
        this->territories->push_back(t);
    }
}

// assignment operator
Player& Player::operator=(const Player& player) {
    // if it's the same as the present player, don't change anything
    if (this == &player) {
        return *this;
    } else {
        // change data members so that they match
        this->name = player.name;
        this->armyCount = player.armyCount;
        this->reinforcementPool = player.reinforcementPool;
        territories->clear();
        for (const auto& t: *player.territories) {
            this->territories->push_back(t);
        }
        this->cardHand = make_unique<Hand>(*player.cardHand);
        this->ordersList = make_unique<OrdersList>(*player.ordersList);
        this->setNegotiatedPlayers(player.negotiatedPlayers);
        this->hasConqueredTerritory = player.hasConqueredTerritory;
        return *this;
    }
}

// stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "name: " << player.name << ", ";
    os << "armyCount: " << player.armyCount << ", ";
    os << "reinforcementPool: " << player.reinforcementPool << endl;
    os << "Territories:\n";
    // make sure territories isn't null before iterating over it
    if (player.territories) {
        for (const auto& t : *player.territories) {
            os << *t;
        }
    } else {
        os << "null\n";
    }

    os << *player.cardHand << endl;
    os << "Orders: " << *player.ordersList << endl;
    os << "negotiatedPlayers: ";
    if (player.negotiatedPlayers) {
        for (const auto& p : *player.negotiatedPlayers) {
            os << p->getName() << "  ";
        }
    }
    os << "\nhasConqueredTerritory: " << player.hasConqueredTerritory;
    os << "\nplayerStrategy: " << player.playerStrategy->getStrategyName() << endl;

    return os;
}

// getters and setters
string Player::getName() {
    return name;
}

int Player::getArmyCount() const {
    return armyCount;
}

void Player::setArmyCount(int armyCount) {
    Player::armyCount = armyCount;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int reinforcementPool) {
    Player::reinforcementPool = reinforcementPool;
}

const unique_ptr<Hand> &Player::getCardHand() const {
    return cardHand;
}

void Player::setCardHand(unique_ptr<Hand> &cardHand) {
    Player::cardHand = std::move(cardHand);
}

const unique_ptr<vector<shared_ptr<Territory>>> &Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(unique_ptr<vector<shared_ptr<Territory>>> &territories) {
    if (territories) {
        this->territories = std::move(territories);
        for (const auto& territory : *this->territories) {
            auto playerInPossession = this->name;
            territory->setPlayerInPossession(playerInPossession);
        }
    }
}

const shared_ptr<OrdersList> &Player::getOrdersList() const {
    return ordersList;
}

void Player::setOrdersList(unique_ptr<OrdersList> &ordersList) {
    Player::ordersList = std::move(ordersList);
}

const unique_ptr<vector<shared_ptr<Player>>> &Player::getNegotiatedPlayers() const {
    return negotiatedPlayers;
}

void Player::setNegotiatedPlayers(const unique_ptr<vector<shared_ptr<Player>>> &negotiatedPlayers) {
    for (const auto& player : *negotiatedPlayers) {
        this->negotiatedPlayers->push_back(player);
    }
}

bool Player::getHasConqueredTerritory() const {
    return hasConqueredTerritory;
}

void Player::setHasConqueredTerritory(bool hasConqueredTerritory) {
    Player::hasConqueredTerritory = hasConqueredTerritory;
}

const shared_ptr<PlayerStrategy> &Player::getPlayerStrategy() {
    return playerStrategy;
}

template <typename T>
void Player::setPlayerStrategy(shared_ptr<T> &playerStrategy) {
    Player::playerStrategy = std::move(playerStrategy);
}

template void Player::setPlayerStrategy<Human>(shared_ptr<Human>& playerStrategy);
template void Player::setPlayerStrategy<Aggressive>(shared_ptr<Aggressive>& playerStrategy);
template void Player::setPlayerStrategy<Benevolent>(shared_ptr<Benevolent>& playerStrategy);
template void Player::setPlayerStrategy<Neutral>(shared_ptr<Neutral>& playerStrategy);
template void Player::setPlayerStrategy<Cheater>(shared_ptr<Cheater>& playerStrategy);

bool Player::hasOrders() const {
    return !ordersList->getOrderList()->empty();
}

// destructor
Player::~Player() = default; // deletion of data members handled by smart pointers already

/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toDefend() {
    return playerStrategy->toDefend();
}

/**
 * Returns a list of territories to attack.
 * @return list of territories to attack
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toAttack() {
    return playerStrategy->toAttack();
}


/**
 * Creates an order and adds it to the list of orders.
 * @param order
 */
void Player::issueOrder() {
    playerStrategy->issueOrder();
}

void Player::addTerritory(const shared_ptr<Territory>& territory) {
    // add territory to territories vector
    this->territories->push_back(territory);

    // change player in possession
    territory->setPlayerInPossession(this->name);
}

void Player::removeTerritory(const shared_ptr<Territory>& territory) {
    // find the territory
    auto iterator = find_if(this->territories->begin(), this->territories->end(),
                            [territory](const shared_ptr<Territory>& t) {
        return t->getId() == territory->getId();
    });

    if (iterator != this->territories->end()) {
        // territory is found, remove it
        this->territories->erase(iterator);
        // update army count
        this->armyCount -= *territory->getArmyCnt();
    }
}

void Player::removeTerritory(const shared_ptr<Territory> &territory, const shared_ptr<Player> &newOwner) {
    removeTerritory(territory);
    // change player in possession
    territory->setPlayerInPossession(newOwner->getName());
}

/**
 * Clean up territories to remove territories not owned by the player anymore.
 */
void Player::updateTerritories() {
    for (const auto& territory : *this->territories) {
        territory->setWasAttacked(false);
        if (territory->getPlayerInPossession() != this->name) {
            this->removeTerritory(territory);
        }
    }
}

void Player::addNegotiatedPlayer(const shared_ptr<Player>& player) {
    this->negotiatedPlayers->push_back(player);
}

void Player::clearNegotiatedPlayers() {
    this->negotiatedPlayers->clear();
}

bool Player::isInNegotiatedPlayers(string playerName) {
    return any_of(this->negotiatedPlayers->begin(),
                  this->negotiatedPlayers->end(),
                  [&](const auto& player) {
        return player->getName() == playerName;
    });
}

int Player::updateArmyCount() {
    int newArmyCount = 0;
    for (const auto& territory : *this->territories) {
        newArmyCount += *territory->getArmyCnt();
    }
    this->armyCount = newArmyCount;
    return newArmyCount;
}

/**
 * Checks if the player has conquered any territory this turn, and if so
 * draws a card from the deck and adds it to the player's hand of cards.
 *
 * Meant to be called at the end of every turn.
 * @param deck shared pointer to the deck of cards used during the game
 */
void Player::drawIfHasConquered(const shared_ptr<Deck> &deck) {
    if (hasConqueredTerritory) {
        Card* card = deck->draw();
        this->cardHand->addCardToHand(card);
    }
}

/**
 * Checks whether the given card type is within the cards that the player has played.
 * @param cardType the type of the card to be checked
 * @return whether the given card type is within the cards that the player has played
 */
bool Player::hasPlayedCard(const string& cardType) {
    return Hand::findFirstCard(this->cardHand->getPlayCards(), cardType) != -1;
}

bool Player::hasCardInHand(const string &cardType) {
    return Hand::findFirstCard(this->cardHand->getHandOfCards(), cardType) != -1;
}

/**
 * Plays a card of the given type that the player has in their hand.
 * @param deck shared ptr to the deck
 * @param cardType the type of card that needs to be played
 */
void Player::playCard(const shared_ptr<Deck> &deck, const string &cardType) {
    if (this->hasCardInHand(cardType)) {
        // get the card
        int cardIndex = Hand::findFirstCard(this->cardHand->getHandOfCards(), cardType);
        auto handOfCards = *this->cardHand->getHandOfCards();
        Card* card = handOfCards[cardIndex];
        // get the deck pointer
        Deck* deckPtr = deck.get();
        // play the card
        this->cardHand->play(card, deckPtr);
    }
}

/**
 * Checks if the player has been attacked at any time this turn.
 * @return true if the player was attacked
 */
bool Player::wasAttacked() {
    // Check if any territories owned by the player have changed ownership
    for (auto& territory : *this->territories) {
        if (territory->territoryWasAttacked() == true) {
            // owned or previously owned territory was attacked, so player has been attacked
            return true;
        }
    }

    // No territories have changed ownership
    return false;
}

/**
 * Updates all the player data members that need to be updated after every turn
 * and executes any additional actions that need to be done every turn.
 *
 * Updates to be done every turn:
 * 1) update army count
 * 2) update reinforcement pool
 * 3) update territories
 * 4) clear negotiated players
 * 5) draw if hasConqueredTerritory
 * 6) clear hasConqueredTerritory
 * 7) clear player's played cards
 *
 * This method is meant to be called at the end of every turn on every player.
 *
 * @param deck shared pointer to the deck of cards used during the game
 */
void Player::update(const shared_ptr<Deck>& deck) {
    this->updateArmyCount();
    this->reinforcementPool = max(3, this->armyCount/2); // I don't know the rule
    this->updateTerritories();
    this->clearNegotiatedPlayers();
    this->drawIfHasConquered(deck);
    this->hasConqueredTerritory = false;
    this->cardHand->clearPlayedCards();
}








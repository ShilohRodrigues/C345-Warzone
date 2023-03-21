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
    os << "\nhasConqueredTerritory: " << player.hasConqueredTerritory << endl;

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

const unique_ptr<OrdersList> &Player::getOrdersList() const {
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

bool Player::hasOrders() const {
    return !ordersList->getOrderList()->empty();
}

// destructor
Player::~Player() = default; // deletion of data members handled by smart pointers already


// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toDefend() {
    // TODO: not arbitrary anymore
    auto arbitraryList = make_unique<vector<shared_ptr<Territory>>>();
    arbitraryList->push_back(this->territories->at(0));
    arbitraryList->push_back(this->territories->at(1));

    return arbitraryList;
}

// toAttack()
/**
 * Returns a list of territories to attack.
 * @return list of territories to attack
 */
unique_ptr<vector<shared_ptr<Territory>>> Player::toAttack() {
    // TODO: not arbitrary anymore
    auto arbitraryList = make_unique<vector<shared_ptr<Territory>>>();
    arbitraryList->push_back(this->territories->at(2));
    arbitraryList->push_back(this->territories->at(3));

    return arbitraryList;
}


// issueOrder()
/**
 * Creates an order and adds it to the list of orders.
 * @param order
 */
void Player::issueOrder() {
    Map* map = new Map();
    // The player decides which territories are to be defended in priority (as a list return by the toDefend() method).
    auto territoriesToDefend = toDefend();
    // The player decides which adjacent territories are to be attacked in priority (as a list return by the toAttack() method).
    auto territoriesToAttack = toAttack();

    // The player issues deploy orders on its own territories that are in the list returned by toDefend().
    // As long as the player has armies still to deploy, it will issue a deploy order and no other order.
    // Once it has deployed all its  armies, it can proceed with other kinds of orders.
    for (const auto& territory : *territoriesToDefend) {
        // check if player has armies to deploy
        while (this->reinforcementPool > 0) {
            // create deploy order
            auto deployOrder = make_shared<Deploy>(make_shared<Player>(*this), territory, this->reinforcementPool);
            // add deploy order to orders list
            this->ordersList->add(deployOrder);
            // decrement reinforcement pool
            this->reinforcementPool--;
        }
    }

    // The player issues advance orders to either:(1) move armies from one of its own territory to the other in order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its territories to a neighboring enemy territory to attack them (using toAttack() to make the decision).
    for (const auto& territory : *territoriesToAttack) {
        // check if player has armies to deploy
        while (this->reinforcementPool > 0) {
            // create deploy order
            auto deployOrder = make_shared<Deploy>(make_shared<Player>(*this), territory, this->reinforcementPool);
            // add deploy order to orders list
            this->ordersList->add(deployOrder);
            // decrement reinforcement pool
            this->reinforcementPool--;
        }
    }

    // get a shared_ptr to the deck object
    auto sharedDeck = std::make_shared<Deck>();
    // check if the player has any cards
    auto handOfCards = this->getCardHand()->getHandOfCards();
    // if the player has any card in their hand of cards, let them choose one to play
    if (!handOfCards->empty()) {
        // display the player's hand of cards and prompt them to choose one
        cout << "Your hand of cards: " << endl;
        for (size_t i = 0; i < handOfCards->size(); i++) {
            cout << i << ": " << handOfCards->at(i)->getCardType() << " " << endl;
        }
        cout << "Choose a card to play (enter the index): " << endl;
        // get the player's choice
        size_t choice;
        cin >> choice;
        // check if the choice is valid
        if (choice < handOfCards->size()) {
            // play the chosen card
            auto chosenCard = handOfCards->at(choice);
            ////this->playCard(sharedDeck, chosenCard->getCardType());
            auto cardType = chosenCard->getCardType();

            // execute the corresponding method for the card type
            if (cardType == "Bomb") {
                // prompt the player to choose a target territory
                cout << "Choose a territory to bomb: " << endl;
                auto targetTerritory = map->getTerritories();
                // create the bomb order
                auto playerPtr = make_shared<Player>(*this);
                auto bombOrder = make_shared<Bomb>(playerPtr, targetTerritory);
                // execute the bomb order
                bombOrder->execute();
            }
            else if (cardType == "Blockade") {
                cout << "Choose a territory to blockade: " << endl;
                auto targetTerritory = map->getTerritories();
                // Create a neutral player
                auto neutralPlayer = make_shared<Player>("Neutral");
                // Create the blockade order
                auto playerPtr = make_shared<Player>(*this);
                auto blockadeOrder = make_shared<Blockade>(playerPtr, neutralPlayer, targetTerritory);
                // Execute the blockade order
                blockadeOrder->execute();
            }
            else if (cardType == "Airlift") {
                cout << "Choose the source territory: " << endl;
                auto allTerritories = map->getTerritories();
                int sourceTerritoryIndex;
                cin >> sourceTerritoryIndex;

                auto sourceTerritoryIt = allTerritories.begin();
                std::advance(sourceTerritoryIt, sourceTerritoryIndex - 1);
                auto sourceTerritory = sourceTerritoryIt->second;

                cout << "Choose the target territory: " << endl;
                auto targetTerritories = map->getTerritories();
                int targetTerritoryIndex;
                cin >> targetTerritoryIndex;

                auto targetTerritoryIt = allTerritories.begin();
                std::advance(targetTerritoryIt, targetTerritoryIndex - 1);
                auto targetTerritory = targetTerritoryIt->second;

                cout << "Enter the number of armies to airlift: " << endl;
                auto numArmies = getArmyCount();
                cin >> numArmies;
                // create the airlift order
                auto playerPtr = make_shared<Player>(*this);
                auto airliftOrder = make_shared<Airlift>(playerPtr, sourceTerritory, targetTerritory, numArmies);
                // execute the airlift order
                airliftOrder->execute();
            }
            else if (cardType == "Diplomacy") {
                // Get the list of all players in the game
                auto players = getGameEngine()->getPlayers();

                cout << "Choose a player to negotiate with: " << endl;
                for (size_t i = 0; i < players.size(); ++i) {
                    cout << i + 1 << ": " << players[i].getName() << endl;
                }

                size_t targetPlayerIndex;
                cin >> targetPlayerIndex;

                if (targetPlayerIndex >= 1 && targetPlayerIndex <= players.size()) {
                    auto targetPlayer = players[targetPlayerIndex - 1];

                    // Check if the target player is not the same as the issuer
                    if (targetPlayer.getName() != this->getName()) {
                        
                        auto NegotiateOrder = make_shared<Negotiate>(this->getName(), targetPlayer);
                        NegotiateOrder->execute();
                    }
                }
                else {
                    cout << "Invalid choice. Please choose a valid player index." << endl;
                }
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        else {
            cout << "You have no cards in your hand." << endl;
        }
    }
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
    this->reinforcementPool = this->armyCount;
    this->updateTerritories();
    this->clearNegotiatedPlayers();
    this->drawIfHasConquered(deck);
    this->hasConqueredTerritory = false;
    this->cardHand->clearPlayedCards();
}






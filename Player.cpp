#include "Player.h"
#include <algorithm>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "GameEngine.h"

using namespace std;

int Player::nextID = 0;

// default constructor
Player::Player() :
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
    hasConqueredTerritory(false){
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
    hasConqueredTerritory(false){
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
    hasConqueredTerritory(player.hasConqueredTerritory){
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
// part 3 add
bool Player::hasOrders() const {
    return !ordersList->getOrderList()->empty();
}

// part 3 add
//int Player::getNumTerritoriesOwned() const {
//    return numTerritoriesOwned;
//}
//void Player::setNumTerritoriesOwned(int numTerritoriesOwned) {
//    this->numTerritoriesOwned = numTerritoriesOwned;
//}

// destructor
Player::~Player() = default; // deletion of data members handled by smart pointers already

shared_ptr<Territory> Player::getTerritoryByID(int territoryID) const {
    for (const auto& territory : *territories) {
        if (territory->getId() == territoryID) {
            return territory;
        }
    }
    // Return nullptr if the territory is not found
    return nullptr;
}

 // toAttack()
 /**
  * Returns a list of territories to attack.
  * @return list of territories to attack
  */
list<shared_ptr<Territory>> Player::toAttack() {
    list<shared_ptr<Territory>> attackList;
    cout << "The list of territories to attack:" << endl;
    for (const auto& territory : *territories) {
        if (territory->getPlayerInPossession() != getName()) {
            // Iterate over adjacent territories and check if they are not owned by the player
            for (int adjacentTerritoryID : *territory->getAdjacentTerritories()) {
                shared_ptr<Territory> adjacentTerritory = getTerritoryByID(adjacentTerritoryID);
                if (adjacentTerritory->getPlayerInPossession() != getName()) {
                    attackList.push_back(adjacentTerritory);
                }
            }
        }
    }
    return attackList;
}

// toDefend()
/**
 * Returns a list of territories to defend.
 * @return list of territories to defend
 */
list<shared_ptr<Territory>> Player::toDefend() {
    list<shared_ptr<Territory>> defendList;
    cout << "The list of territories to defend:" << endl;
    // Iterate through the territories owned by the player
    for (const auto& territory : *territories) {
        // Add the territory to the defendList since the player owns it
        if (territory->getPlayerInPossession() == getName()) {
            defendList.push_back(territory);
        }
    }
    return defendList;
}


// issueOrder()
/**
 * Creates an order and adds it to the list of orders.
 * @param order
 */
void Player::issueOrder() {
    list<shared_ptr<Territory>> territoriesToAttack = toAttack();
    list<shared_ptr<Territory>> territoriesToDefend = toDefend();

    // Deploy orders
    while (armyCount > 0) {
        for (const auto& territory : territoriesToDefend) {
            if (armyCount > 0) {
                //---------------------------------------------------- deploy argument problem
                auto deployOrder = make_shared<Deploy>(this, territory.get(), getReinforcementPool());
                    deployOrder->execute();
                    armyCount--;
            }
        }
    }

    // Advance orders for defense
    for (const auto& CurrentTerritory : territoriesToDefend) {
        const unique_ptr<int>& armyCnt = CurrentTerritory->getArmyCnt();
        if (*armyCnt > 1) {
            cout << "You have " << *armyCnt << " armies in " << CurrentTerritory->getName() << ". How many armies would you like to move to defend your territories? ";
            int armiesToMove;
            cin >> armiesToMove;
            for (const auto& target : territoriesToDefend) {
                if (target != CurrentTerritory) {
                    //---------------------------------------------------- advance argument problem
                    auto advanceOrder = make_shared<Advance>(this, CurrentTerritory, target, armiesToMove);
                        advanceOrder->execute();
                    break;
                }
            }
        }
    }

    // Advance orders for attack
    for (const auto& CurrentTerritory : territoriesToDefend) {
        const unique_ptr<int>& armyCnt = CurrentTerritory->getArmyCnt();
        if (*armyCnt > 1) {
            cout << "You have " << *armyCnt << " armies in " << CurrentTerritory->getName() << ". How many armies would you like to move to attack your enemy territories? ";
            int armiesToMove;
            cin >> armiesToMove;
            for (const auto& target : territoriesToAttack) {
                if (find(CurrentTerritory->getAdjacentTerritories()->begin(), CurrentTerritory->getAdjacentTerritories()->end(), target->getId()) != CurrentTerritory->getAdjacentTerritories()->end()) {
                    //---------------------------------------------------- advance argument problem
                    auto advanceOrder = make_shared<Advance>(this, CurrentTerritory, target, armiesToMove);
                        advanceOrder->execute();
                    break;
                }
            }
        }
    }

    // check if the player has any cards
    auto playerCards = this->getCardHand()->getHandOfCards();
    // if the player has any card in their hand of cards, let them choose one to play
    if (!playerCards->empty()) {
        // display the player's hand of cards and prompt them to choose one
        cout << "Your hand of cards: " << endl;
        for (size_t i = 0; i < playerCards->size(); i++) {
            cout << i << ": " << playerCards->at(i)->getCardType() << " " << endl;
        }

        cout << "Choose a card to play (enter the number): " << endl;
        // get the player's choice
        size_t choice;
        cin >> choice;

        // check if the choice is valid
        if (choice < playerCards->size()) {
            // play the chosen card
            auto chosenCard = playerCards->at(choice);
            auto type = chosenCard->getCardType();

            // execute the corresponding method for the card type
            //---------------------------------------------------- bomb argument problem
            if (type == "Bomb") {
                // Get the list of enemy territories
                list<shared_ptr<Territory>> enemyTerritories = toAttack();

                // Display the list of enemy territories
                cout << "Choose a territory to bomb:" << endl;
                size_t index = 0;
                for (const auto& territory : enemyTerritories) {
                    cout << index << ": " << territory->getName() << " (" << territory->getPlayerInPossession() << ")" << endl;
                    index++;
                }

                // Get the player's choice
                size_t target;
                cout << "Enter the number of the target territory: ";
                cin >> target;

                // Check if the choice is valid
                if (target < enemyTerritories.size()) {
                    // Find the chosen territory
                    auto targetTerritory = std::next(enemyTerritories.begin(), target);

                    // Create and execute a Bomb order
                    auto bombOrder = make_shared<Bomb>(this, *targetTerritory);
                    bombOrder->execute();
                }
                else {
                    cout << "Invalid target." << endl;
                }
            }
            //---------------------------------------------------- player, blockade argument problem
            else if (type == "Blockade") {
                // Get the list of player's territories
                list<shared_ptr<Territory>> playerTerritories = toDefend();

                // Display the list of player's territories
                cout << "Choose a territory to blockade:" << endl;
                size_t index = 0;
                for (const auto& territory : playerTerritories) {
                    cout << index << ": " << territory->getName() << " (" << territory->getPlayerInPossession() << ")" << endl;
                    index++;
                }

                // Get the player's choice
                size_t target;
                cout << "Enter the number of the target territory: ";
                cin >> target;

                // Check if the choice is valid
                if (target < playerTerritories.size()) {
                    // Find the chosen territory
                    auto targetTerritory = std::next(playerTerritories.begin(), target);

                    // Create a neutral player
                    auto neutralPlayer = make_shared<Player>("Neutral");

                    // Create and execute a Blockade order
                    auto blockadeOrder = make_shared<Blockade>(this, neutralPlayer, *targetTerritory);
                    blockadeOrder->execute();
                }
                else {
                    cout << "Invalid target." << endl;
                }
            }
            //---------------------------------------------------- airlift argument problem
            else if (type == "Airlift") {
                // Get the list of player's territories
                list<shared_ptr<Territory>> playerTerritories = toDefend();

                // Display the list of player's territories
                cout << "Choose a source territory to airlift armies from:" << endl;
                size_t index = 0;
                for (const auto& territory : playerTerritories) {
                    cout << index << ": " << territory->getName() << " (" << territory->getPlayerInPossession() << ")" << endl;
                    index++;
                }

                // Get the player's choice for the source territory
                size_t sourceIdx;
                cout << "Enter the number of the source territory: ";
                cin >> sourceIdx;

                // Check if the choice is valid
                if (sourceIdx < playerTerritories.size()) {
                    // Find the chosen source territory
                    auto sourceTerritory = std::next(playerTerritories.begin(), sourceIdx);

                    // Display the list of player's territories again
                    cout << "Choose a target territory to airlift armies to:" << endl;
                    index = 0;
                    for (const auto& territory : playerTerritories) {
                        cout << index << ": " << territory->getName() << " (" << territory->getPlayerInPossession() << ")" << endl;
                        index++;
                    }

                    // Get the player's choice for the target territory
                    size_t targetIdx;
                    cout << "Enter the number of the target territory: ";
                    cin >> targetIdx;

                    // Check if the choice is valid
                    if (targetIdx < playerTerritories.size()) {
                        // Find the chosen target territory
                        auto targetTerritory = std::next(playerTerritories.begin(), targetIdx);

                        // Ask the player for the number of armies to airlift
                        int airliftArmies;
                        cout << "Enter the number of armies to airlift: ";
                        cin >> airliftArmies;

                        // Create and execute an Airlift order
                        auto airliftOrder = make_shared<Airlift>(this, *sourceTerritory, *targetTerritory, airliftArmies);
                        airliftOrder->execute();
                    }
                    else {
                        cout << "Invalid target." << endl;
                    }
                }
                else {
                    cout << "Invalid source." << endl;
                }
            }

            else if (type == "Diplomacy") {
                // Get the list of players
                list<string> playerNames;
                for (const auto& territory : *territories) {
                    string playerName = territory->getPlayerInPossession();
                    // not current player, not mentioned --> add player
                    if (playerName != getName() && find(playerNames.begin(), playerNames.end(), playerName) == playerNames.end()) {
                        playerNames.push_back(playerName);
                    }
                }

                // Display the list of players
                cout << "Choose a player to negotiate with:" << endl;
                size_t index = 0;
                for (const string& playerName : playerNames) {
                    cout << index << ": " << playerName << endl;
                    index++;
                }

                // Get the player's choice
                size_t choice;
                cout << "Enter the number of the player to negotiate with: ";
                cin >> choice;

                // Check if the choice is valid
                if (choice < playerNames.size()) {
                    // Find the chosen player
                    string chosenPlayerName = *next(playerNames.begin(), choice);
                    shared_ptr<Player> targetPlayer;
                    for (const auto& player : *players) {
                        if (player->getName() == chosenPlayerName) {
                            targetPlayer = player;
                            break;
                        }
                    }

                    // Create and execute a Negotiate order
                    auto negotiateOrder = make_shared<Negotiate>(this, targetPlayer);
                    negotiateOrder->execute();
                }
                else {
                    cout << "Invalid player choice." << endl;
                }
             }

            // remove the played card from the player's hand  --> already implemented in each orders
            //this->getCardHand()->deletePlayedCardFromHand(chosenCard);
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
    else {
        cout << "You have no cards in your hand." << endl;
    }
}

void Player::addTerritory(const shared_ptr<Territory>& territory) {
    // add territory to territories vector
    this->territories->push_back(territory);

    // change player in possession
    territory->setPlayerInPossession(this->name);

    // part 3 add
    // update numTerritoriesOwned
    /*setNumTerritoriesOwned(this->territories->size());*/
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

        // part 3 add
        // update numTerritoriesOwned
        /*setNumTerritoriesOwned(this->territories->size());*/
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






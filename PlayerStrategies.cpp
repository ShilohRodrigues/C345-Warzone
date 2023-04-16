#include "PlayerStrategies.h"
#include "Orders.h"
#include <random>
#include <set>

using namespace std;

// default constructor
PlayerStrategy::PlayerStrategy(shared_ptr<Player> player):
    player(player), strategyName("") {}

// copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy &playerStrategy):
    player(playerStrategy.player), strategyName(playerStrategy.strategyName) {}

// assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy &playerStrategy) {
    this->player = playerStrategy.player;
    this->strategyName = playerStrategy.strategyName;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const PlayerStrategy& playerStrategy) {
    os << "strategy: " << playerStrategy.strategyName;
    return os;
}

unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> PlayerStrategy::getToAttackMap() {
    return nullptr;
}

// getters and setters
const shared_ptr<Player> &PlayerStrategy::getPlayer() const {
    return player;
}

void PlayerStrategy::setPlayer(shared_ptr<Player> &player) {
    PlayerStrategy::player = player;
}

const string &PlayerStrategy::getStrategyName() const {
    return strategyName;
}

void PlayerStrategy::setStrategyName(const string &strategyName) {
    PlayerStrategy::strategyName = strategyName;
}

// -- HUMAN player strategy --
// default constructor
Human::Human(shared_ptr<Player> player): PlayerStrategy(player) {
    this->strategyName = strategyName;
}

// copy constructor
Human::Human(const Human &human): PlayerStrategy(human) {}

// assignment operator
Human& Human::operator=(const Human& human) {
    this->player = human.player;
    this->strategyName = human.strategyName;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Human& human) {
    os << "strategy: " << human.strategyName;
    return os;
}

void Human::issueOrder() {
//    Map* map = new Map();
//    // The player decides which territories are to be defended in priority (as a list return by the toDefend() method).
//    auto territoriesToDefend = toDefend();
//    // The player decides which adjacent territories are to be attacked in priority (as a list return by the getToAttackMap() method).
//    auto territoriesToAttack = getToAttackMap();
//
//    // The player issues deploy orders on its own territories that are in the list returned by toDefend().
//    // As long as the player has armies still to deploy, it will issue a deploy order and no other order.
//    // Once it has deployed all its  armies, it can proceed with other kinds of orders.
//    for (const auto& territory : *territoriesToDefend) {
//        // check if player has armies to deploy
//        while (this->reinforcementPool > 0) {
//            // create deploy order
//            auto deployOrder = make_shared<Deploy>(make_shared<Player>(*this), territory, this->reinforcementPool);
//            // add deploy order to orders list
//            this->ordersList->add(deployOrder);
//            // decrement reinforcement pool
//            this->reinforcementPool--;
//        }
//    }
//
//    // The player issues advance orders to either:(1) move armies from one of its own territory to the other in order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its territories to a neighboring enemy territory to attack them (using getToAttackMap() to make the decision).
//    for (const auto& territory : *territoriesToAttack) {
//        // check if player has armies to deploy
//        while (this->reinforcementPool > 0) {
//            // create deploy order
//            auto deployOrder = make_shared<Deploy>(make_shared<Player>(*this), territory, this->reinforcementPool);
//            // add deploy order to orders list
//            this->ordersList->add(deployOrder);
//            // decrement reinforcement pool
//            this->reinforcementPool--;
//        }
//    }
//
//    // get a shared_ptr to the deck object
//    auto sharedDeck = std::make_shared<Deck>();
//    // check if the player has any cards
//    auto handOfCards = this->getCardHand()->getHandOfCards();
//    // if the player has any card in their hand of cards, let them choose one to play
//    if (!handOfCards->empty()) {
//        // display the player's hand of cards and prompt them to choose one
//        cout << "Your hand of cards: " << endl;
//        for (size_t i = 0; i < handOfCards->size(); i++) {
//            cout << i << ": " << handOfCards->at(i)->getCardType() << " " << endl;
//        }
//        cout << "Choose a card to play (enter the index): " << endl;
//        // get the player's choice
//        size_t choice;
//        cin >> choice;
//        // check if the choice is valid
//        if (choice < handOfCards->size()) {
//            // play the chosen card
//            auto chosenCard = handOfCards->at(choice);
//            ////this->playCard(sharedDeck, chosenCard->getCardType());
//            auto cardType = chosenCard->getCardType();
//
//            // execute the corresponding method for the card type
//            if (cardType == "Bomb") {
//                // prompt the player to choose a target territory
//                cout << "Choose a territory to bomb: " << endl;
//                auto targetTerritory = map->getTerritories();
//                // create the bomb order
//                auto playerPtr = make_shared<Player>(*this);
////                auto bombOrder = make_shared<Bomb>(playerPtr, targetTerritory);
//                // execute the bomb order
////                bombOrder->execute();
//            }
//            else if (cardType == "Blockade") {
//                cout << "Choose a territory to blockade: " << endl;
//                auto targetTerritory = map->getTerritories();
//                // Create a neutral player
////                auto neutralPlayer = make_shared<Player>("Neutral");
//                // Create the blockade order
//                auto playerPtr = make_shared<Player>(*this);
////                auto blockadeOrder = make_shared<Blockade>(playerPtr, neutralPlayer, targetTerritory);
//                // Execute the blockade order
////                blockadeOrder->execute();
//            }
//            else if (cardType == "Airlift") {
//                cout << "Choose the source territory: " << endl;
//                auto allTerritories = map->getTerritories();
//                int sourceTerritoryIndex;
//                cin >> sourceTerritoryIndex;
//
//                auto sourceTerritoryIt = allTerritories.begin();
//                std::advance(sourceTerritoryIt, sourceTerritoryIndex - 1);
//                auto sourceTerritory = sourceTerritoryIt->second;
//
//                cout << "Choose the target territory: " << endl;
//                auto targetTerritories = map->getTerritories();
//                int targetTerritoryIndex;
//                cin >> targetTerritoryIndex;
//
//                auto targetTerritoryIt = allTerritories.begin();
//                std::advance(targetTerritoryIt, targetTerritoryIndex - 1);
//                auto targetTerritory = targetTerritoryIt->second;
//
//                cout << "Enter the number of armies to airlift: " << endl;
//                auto numArmies = getArmyCount();
//                cin >> numArmies;
//                // create the airlift order
//                auto playerPtr = make_shared<Player>(*this);
////                auto airliftOrder = make_shared<Airlift>(playerPtr, sourceTerritory, targetTerritory, numArmies);
//                // execute the airlift order
////                airliftOrder->execute();
//            }
//            else if (cardType == "Diplomacy") {
//                // Get the list of all players in the game
//                auto players = getGameEngine()->getPlayers();
//
//                cout << "Choose a player to negotiate with: " << endl;
//                for (size_t i = 0; i < players.size(); ++i) {
//                    cout << i + 1 << ": " << players[i].getName() << endl;
//                }
//
//                size_t targetPlayerIndex;
//                cin >> targetPlayerIndex;
//
//                if (targetPlayerIndex >= 1 && targetPlayerIndex <= players.size()) {
//                    auto targetPlayer = players[targetPlayerIndex - 1];
//
//                    // Check if the target player is not the same as the issuer
//                    if (targetPlayer.getName() != this->getName()) {
//
////                        auto NegotiateOrder = make_shared<Negotiate>(this->getName(), targetPlayer);
////                        NegotiateOrder->execute();
//                    }
//                }
//                else {
//                    cout << "Invalid choice. Please choose a valid player index." << endl;
//                }
//            }
//            else {
//                cout << "Invalid choice." << endl;
//            }
//        }
//        else {
//            cout << "You have no cards in your hand." << endl;
//        }
//    }
}

unique_ptr<vector<shared_ptr<Territory>>> Human::toAttack() {}

unique_ptr<vector<shared_ptr<Territory>>> Human::toDefend() {}

// -- AGGRESSIVE player strategy --
// default constructor
Aggressive::Aggressive(shared_ptr<Player> player): PlayerStrategy(player) {
    this->strategyName = "Aggressive";
}

// copy constructor
Aggressive::Aggressive(const Aggressive &aggressive): PlayerStrategy(aggressive) {}

// assignment operator
Aggressive& Aggressive::operator=(const Aggressive& aggressive) {
    this->player = aggressive.player;
    this->strategyName = aggressive.strategyName;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Aggressive& aggressive) {
    os << "strategy: " << aggressive.strategyName;
    return os;
}

/**
 * Decides which orders the aggressive player will choose to issue and adds it to the player's orders list.
 * It will deploy or advance armies on its strongest country, then always advance to
 * enemy territories until it can't do so anymore.
 */
void Aggressive::issueOrder() {
    auto attackList = this->getToAttackMap();
    // deploy the player's whole reinforcement pool to the player's strongest territory
    auto strongestTerritory = this->getStrongestTerritory();
    auto deployToStrongest = make_shared<Deploy>(this->player,
                                                 strongestTerritory,
                                                 this->player->getReinforcementPool());
    // add deploy order to player's orders list
    auto ordersList = this->player->getOrdersList();
    ordersList->add(deployToStrongest);

    // issue advance orders to attack adjacent enemy territories
    auto attackMap = this->getToAttackMap();

    // Iterate over all attacking territories (owned by player) and advance armies to attackable territories
    for (auto& attackingTerritory : *attackMap) {
        auto& armyCnt = *attackingTerritory.first->getArmyCnt();

        // Define a random number generator
        random_device rd;
        mt19937 rng(rd());

        // Choose a random target territory from the list of attackable territories
        uniform_int_distribution<int> distribution(0, attackingTerritory.second.size() - 1);

        auto randomIndex = distribution(rng);
        auto targetTerritory = attackingTerritory.second[randomIndex];

        if (armyCnt > 0) {
            // Randomly select the number of armies to advance to the target territory
            uniform_int_distribution<int> armiesDistribution(1, armyCnt);
            auto numArmiesToAdvance = armiesDistribution(rng);

            // Create and execute an Advance order to advance the armies to the target territory
            auto advanceOrder = make_shared<Advance>(this->player,
                                                     attackingTerritory.first, targetTerritory,
                                                     numArmiesToAdvance);
            // add the order to the player's order list
            ordersList->add(advanceOrder);
        }
    }
}

/**
 * Returns the strongest territory owned by the player, based on the number of armies it contains.
 *
 * @return A shared_ptr to the strongest territory owned by the player.
 */
shared_ptr<Territory> Aggressive::getStrongestTerritory() {
    // Sort the player's territories based on their number of armies in descending order
    auto& sortedTerritories = *this->player->getTerritories();
    sort(sortedTerritories.begin(), sortedTerritories.end(),
         [](auto t1, auto t2) {
             return *t1->getArmyCnt() > *t2->getArmyCnt();
         });

    // the strongest territory owned by the player is the first one
    return sortedTerritories[0];
}

/**
 * Returns a unique pointer to an unordered map that contains the territories to attack for an aggressive player.
 * The keys of the map are the territories owned by the player that have armies greater than 1 and have adjacent enemy territories.
 * The values of the map are vectors of pointers to the adjacent enemy territories with armies.
 * @return a unique pointer to an unordered map of territories to attack for an aggressive player.
 */
unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> Aggressive::getToAttackMap() {
    auto attackMap = make_unique<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>>();

    // Get all territories owned by the player
    auto& playerTerritories = *player->getTerritories();

    // Iterate over all player territories and add adjacent enemy territories with armies to the attack map
    for (auto& territory : playerTerritories) {
        auto adjacentTerritories = territory->getAdjacentTerritoriesPointers();
        for (auto& t : *adjacentTerritories) {
            // if the territory is not owned by the player (enemy territory)
            if (!(t->getPlayerInPossession() == player->getName())) {
                if (*territory->getArmyCnt() > 0) {
                    // If the attacking territory is not in the map yet, add it with an empty vector of targets
                    if (attackMap->find(territory) == attackMap->end()) {
                        (*attackMap)[territory] = vector<shared_ptr<Territory>>();
                    }
                    // Add the target territory to the list of targets for the attacking territory
                    (*attackMap)[territory].push_back(t);
                }
            }
        }
    }

    return attackMap;
}

/**
 * Generates a list of all territories that can be attacked by the player, without duplicates.
 *
 * @return A unique_ptr to a vector of shared_ptr<Territory> objects representing the territories
 * that the player can attack without duplicates.
 */
unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toAttack() {
    auto attackMap = Aggressive::getToAttackMap();

    auto attackableTerritories = make_unique<vector<shared_ptr<Territory>>>();

    // Iterate over the attack map and add all target territories to the vector
    for (const auto& [attackingTerritory, targetTerritories] : *attackMap) {
        for (const auto& targetTerritory : targetTerritories) {
            attackableTerritories->push_back(targetTerritory);
        }
    }

    // Define a custom comparison function that compares shared_ptr<Territory> based on their territoryID
    auto territoryPtrCompare =
            [](const shared_ptr<Territory>& t1, const shared_ptr<Territory>& t2) {
        return t1->getId() < t2->getId();
    };

    // Use std::sort and std::unique with the custom comparison function to remove duplicates from the vector
    std::sort(attackableTerritories->begin(), attackableTerritories->end(), territoryPtrCompare);
    auto last = std::unique(attackableTerritories->begin(), attackableTerritories->end(),
                            territoryPtrCompare);
    attackableTerritories->erase(last, attackableTerritories->end()); // shrink vector

    return attackableTerritories;
}

/**
 * Returns a pointer to the vector of territories to defend.
 * @return An empty territory vector since this player does not care for defense.
 */
unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toDefend() {
    return make_unique<vector<shared_ptr<Territory>>>();
}

// -- BENEVOLENT player strategy --
// default constructor
Benevolent::Benevolent(shared_ptr<Player> player): PlayerStrategy(player) {
    this->strategyName = "Benevolent";
}

// copy constructor
Benevolent::Benevolent(const Benevolent &benevolent): PlayerStrategy(benevolent) {}

// assignment operator
Benevolent& Benevolent::operator=(const Benevolent& benevolent) {
    this->player = benevolent.player;
    this->strategyName = benevolent.strategyName;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Benevolent& benevolent) {
    os << "strategy: " << benevolent.strategyName;
    return os;
}

/**
 * Decides which orders the Benevolent player should issue and adds them to the player's orders list.
 *
 * The Benevolent player focuses on protecting its weak countries by deploying or advancing armies on its weakest countries,
 * and never advances to enemy territories.
 *
 * Deploys one army at a time to the weakest territories until the reinforcement pool is empty.
 * Then, searches for a random adjacent territory to each weak territory that has not yet been reinforced,
 * and that has not been used as a source territory already.
 * If a valid adjacent territory is found, it creates an advance order
 * from the found source territory to the current territory to defend.
 *
 * The method ends once all weak territories are either reinforced or cannot be reinforced anymore.
 */
void Benevolent::issueOrder() {
    auto toDefendList = this->toDefend();
    auto& territories = *this->player->getTerritories();
    auto reinforcementPool = this->player->getReinforcementPool();
    set<int> reinforcedTerritoryIDs;
    set<int> usedSourceTerritoryIDs;

    // deploy orders
    while (reinforcementPool > 0) {
        for (const auto& t : *toDefendList) {
            if (reinforcementPool > 0) {
                // create deploy order to weakest territories 1 army at a time
                auto deployOrder = make_shared<Deploy>(this->player, t, 1);

                // add it to the player's orders list
                this->player->getOrdersList()->add(deployOrder);
                reinforcedTerritoryIDs.insert(t->getId());
                reinforcementPool--; // we do this manually with a copy of the player's reinforcement pool because creating the order itself doesn't decrement it before execution
            }
        }
    }

    // advance orders
    for (const auto& t : *toDefendList) {
        auto it = reinforcedTerritoryIDs.find(t->getId());
        // if the territory to defend has not been reinforced already
        if (it == reinforcedTerritoryIDs.end()) {
            auto& adjacentTerritories = *t->getAdjacentTerritoriesPointers();
            // Define a random number generator
            random_device rd;
            mt19937 rng(rd());

            const int maxTries = 3;
            shared_ptr<Territory> sourceTerritory = nullptr;

            for (int i = 0; i < maxTries; i++) {
                // Choose a random territory from the list of adjacent territories
                if (adjacentTerritories.empty()) {
                    break;
                }
                uniform_int_distribution<int> distribution(0, adjacentTerritories.size() - 1);
                auto randomIndex = distribution(rng);
                sourceTerritory = adjacentTerritories[randomIndex];

                // check that it's not in the territories already reinforced and
                // that it hasn't been used as a source territory already
                if (reinforcedTerritoryIDs.find(sourceTerritory->getId()) == reinforcedTerritoryIDs.end() ||
                    usedSourceTerritoryIDs.find(sourceTerritory->getId()) == usedSourceTerritoryIDs.end()) {
                    // check that it is in the territories to defend
                    if (find_if(toDefendList->begin(), toDefendList->end(),
                                [sourceTerritory](const shared_ptr<Territory>& t)
                                { return t->getId() == sourceTerritory->getId(); }) != toDefendList->end()) {
                        // make sure that it has > 0 armies
                        if (*sourceTerritory->getArmyCnt() > 0) {
                            // eligible! use it
                            usedSourceTerritoryIDs.insert(sourceTerritory->getId());
                            break;
                        }
                    }
                } // else keep trying until you get an adjacent territory that fits or you hit the max tries
            }

            // if an appropriate adjacent territory is found
            if (sourceTerritory != nullptr) {
                // create an advance order from the found source territory to the current territory to defend
                auto advanceOrder = make_shared<Advance>(this->player, sourceTerritory, t, 1);
                // add it to the player's orders list
                this->player->getOrdersList()->add(advanceOrder);
            }
        }
    }
}

/**
 * Returns a vector representing the territories to attack.
 * Since the Benevolent player does not attack, this vector is empty.
 * @return a vector representing the territories to attack.
 */
unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toAttack() {
    // Benevolent players don't attack
    return make_unique<vector<shared_ptr<Territory>>>();
}

/**
 * Returns a vector representing the territories to defend.
 * For the benevolent player, we choose to define this as the weakest half of its territories.
 * @return a vector representing the territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toDefend() {
    // get all territories owned by the player
    auto& playerTerritories = this->player->getTerritories();

    // sort territories by number of armies in ascending order
    sort(playerTerritories->begin(), playerTerritories->end(),
         [](const shared_ptr<Territory>& a, const shared_ptr<Territory>& b) {
        return *a->getArmyCnt() < *b->getArmyCnt();
    });

    // calculate the number of territories to defend
    int numTerritoriesToDefend = playerTerritories->size() / 2;

    // create a list of weakest territories to defend
    auto defendList = make_unique<vector<shared_ptr<Territory>>>();
    for (int i = 0; i < numTerritoriesToDefend; i++) {
        defendList->push_back(playerTerritories->at(i));
    }

    return defendList;
}

// -- NEUTRAL player strategy --
// default constructor
Neutral::Neutral(shared_ptr<Player> player): PlayerStrategy(player) {
    this->strategyName = "Neutral";
}

// copy constructor
Neutral::Neutral(const Neutral &neutral): PlayerStrategy(neutral) {}

// assignment operator
Neutral& Neutral::operator=(const Neutral& neutral) {
    this->player = neutral.player;
    this->strategyName = neutral.strategyName;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Neutral& neutral) {
    os << "strategy: " << neutral.strategyName;
    return os;
}

/**
 * Issues orders for the Neutral player, but since the Neutral player never issues any orders,
 * the method checks if the player got attacked prior to its turn issuing orders,
 * if so, it becomes an aggressive player.
 */
void Neutral::issueOrder() {
    // check if the player was attacked and is not already aggressive
    if (this->player->wasAttacked() && this->player->getPlayerStrategy()->getStrategyName() != "Aggressive") {
        // create an aggressive strategy and assign it to the player
        auto aggressiveStrategy = make_shared<Aggressive>(this->player);
        this->player->setPlayerStrategy(aggressiveStrategy);
    }

    if (this->player->getPlayerStrategy()->getStrategyName() == "Aggressive") {
        // issue orders as an aggressive player
        this->player->issueOrder();
    }
}

/**
 * Returns a vector of territories representing the territories to attack.
 * Since the Neutral player doesn't issue any orders, this vector is empty.
 * @return a vector of territories representing the territories to attack.
 */
unique_ptr<vector<shared_ptr<Territory>>> Neutral::toAttack() {
    // the neutral player doesn't issue any orders
    return make_unique<vector<shared_ptr<Territory>>>();
}

/**
 * Returns a vector of territories representing the territories to defend.
 * Since the Neutral player doesn't issue any orders, this vector is empty.
 * @return a vector of territories representing the territories to attack.
 */
unique_ptr<vector<shared_ptr<Territory>>> Neutral::toDefend() {
    // the neutral player doesn't issue any orders
    return make_unique<vector<shared_ptr<Territory>>>();
}

// -- CHEATER player strategy --
// default constructor
Cheater::Cheater(shared_ptr<Player> player): PlayerStrategy(player) {
    this->strategyName = "Cheater";
    this->canCheat = true;
}

// copy constructor
Cheater::Cheater(const Cheater &cheater): PlayerStrategy(cheater) {
    this->canCheat = cheater.canCheat;
}

// assignment operator
Cheater& Cheater::operator=(const Cheater& cheater) {
    this->player = cheater.player;
    this->strategyName = cheater.strategyName;
    this->canCheat = cheater.canCheat;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Cheater& cheater) {
    os << "strategy: " << cheater.strategyName;
    os << "canCheat: " << cheater.canCheat;
    return os;
}

/**
 * Issues orders for the Cheater player, but since the cheater can automatically conquer all of its adjacent
 * enemy territories, it doesn't need to issue any orders.
 * Instead the method goes through all of the territories to attack and conquers them automatically by
 * changing the player in possession and adding each territory to the player's list of territories.
 * The method uses the canCheat variable to ensure that the player can only cheat once per turn.
 */
void Cheater::issueOrder() {
    // can only cheat once per turn
    if (canCheat) {
        auto attackList = this->toAttack();
        // conquer all territories in the attack list
        for (auto& t : *attackList) {
            // change the territory's owner
            t->setPlayerInPossession(this->player->getName());
            // add the territory to the player's territories
            this->player->addTerritory(t);
        }
        // can't cheat again for the rest of the turn until the Player::update() is called
        canCheat = false;
    }
}

/**
 * Generates a list of territories to attack, in this case all of the enemy territories adjacent to
 * player-owned territories.
 * @return the list of players to attack
 */
unique_ptr<vector<shared_ptr<Territory>>> Cheater::toAttack() {
    auto attackList = make_unique<vector<shared_ptr<Territory>>>();

    for (auto& t : *this->player->getTerritories()) {
        auto adjacentTerritories = t->getAdjacentTerritoriesPointers();
        for (auto& adjacentTerritory : *adjacentTerritories) {
            // Check if the adjacent territory is an enemy territory
            if (adjacentTerritory->getPlayerInPossession() != this->player->getName()) {
                // Add the enemy territory to the attack list
                attackList->push_back(adjacentTerritory);
            }
        }
    }

    return attackList;
}

/**
 * Generates a list of territories to defend, in this case none are required, so the vector is empty.
 * @return the list of territories to defend
 */
unique_ptr<vector<shared_ptr<Territory>>> Cheater::toDefend() {
    // the cheater doesn't need to defend any territories
    return make_unique<vector<shared_ptr<Territory>>>();
}

bool Cheater::getCanCheat() const {
    return canCheat;
}

void Cheater::setCanCheat(bool canCheat) {
    Cheater::canCheat = canCheat;
}



#include "PlayerStrategies.h"
#include "Orders.h"
#include <random>

using namespace std;

// default constructor
PlayerStrategy::PlayerStrategy(shared_ptr<Player> player):
    player(player) {}

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

// -- HUMAN player strategy --
Human::Human(shared_ptr<Player> player): PlayerStrategy(player) {}

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
Aggressive::Aggressive(shared_ptr<Player> player): PlayerStrategy(player) {}

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
Benevolent::Benevolent(shared_ptr<Player> player): PlayerStrategy(player) {}

void Benevolent::issueOrder() {

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
        return a->getArmyCnt() < b->getArmyCnt();
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
Neutral::Neutral(shared_ptr<Player> player): PlayerStrategy(player) {}

void Neutral::issueOrder() {
    cout << "Neutral issueOrder()" << endl;
}

unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> Neutral::getToAttackMap() {

}

unique_ptr<vector<shared_ptr<Territory>>> Neutral::toAttack() { return nullptr; }

unique_ptr<vector<shared_ptr<Territory>>> Neutral::toDefend() {
    auto territories = make_unique<vector<shared_ptr<Territory>>>(*this->player->getTerritories());
    cout << "toDefend() Territories: " << endl;
    for (const auto& t : *territories) {
        cout << "\t" << *t << endl;
    }
    return territories;
}

// -- CHEATER player strategy --
Cheater::Cheater(shared_ptr<Player> player): PlayerStrategy(player) {}

void Cheater::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toAttack() {}

unique_ptr<unordered_map<shared_ptr<Territory>, vector<shared_ptr<Territory>>>> Cheater::getToAttackMap() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toDefend() {

}



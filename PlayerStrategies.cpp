#include "PlayerStrategies.h"

using namespace std;

// default constructor
PlayerStrategy::PlayerStrategy(Player &player):
    player(make_shared<Player>(player)) {}

// getters and setters
const shared_ptr<Player> &PlayerStrategy::getPlayer() const {
    return player;
}

void PlayerStrategy::setPlayer(shared_ptr<Player> &player) {
    PlayerStrategy::player = player;
}

// -- HUMAN player strategy --
Human::Human(Player &player): PlayerStrategy(player) {}

void Human::issueOrder() {
//    Map* map = new Map();
//    // The player decides which territories are to be defended in priority (as a list return by the toDefend() method).
//    auto territoriesToDefend = toDefend();
//    // The player decides which adjacent territories are to be attacked in priority (as a list return by the toAttack() method).
//    auto territoriesToAttack = toAttack();
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
//    // The player issues advance orders to either:(1) move armies from one of its own territory to the other in order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its territories to a neighboring enemy territory to attack them (using toAttack() to make the decision).
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

unique_ptr<vector<shared_ptr<Territory>>> Human::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Human::toDefend() {

}

// -- AGGRESSIVE player strategy --
Aggressive::Aggressive(Player &player): PlayerStrategy(player) {}

/**
 * Decides which orders the aggressive player will choose to issue.
 * It will deploy or advance armies on its strongest country, then always advance to
 * enemy territories until it can't do so anymore
 */
void Aggressive::issueOrder() {

}

/**
 * Gets the strongest player territory and returns a pointer to a vector of its
 * adjacent enemy territories as territories to attack.
 * @return a pointer to the vector of territories to attack.
 */
unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toAttack() {
    // Sort the player's territories based on their number of armies in descending order
    auto sortedTerritories = *this->player->getTerritories();
    sort(sortedTerritories.begin(), sortedTerritories.end(),
         [](auto t1, auto t2) {
        return *t1->getArmyCnt() > *t2->getArmyCnt();
    });

    // Get the strongest territory owned by the player
    auto strongestTerritory = sortedTerritories[0];

    // Add all adjacent enemy territories to the attack list
    auto attackList = make_unique<vector<shared_ptr<Territory>>>();
    auto adjacentTerritories = strongestTerritory->getAdjacentTerritoriesPointers();
    for (auto& t : *adjacentTerritories) {
        // if the territory is not owned by the player
        if (!(t->getPlayerInPossession() == this->player->getName())) {
            // add to the attack list
            attackList->push_back(t);
        }
    }

    return attackList;
}

/**
 * Returns a pointer to the vector of territories to defend.
 * @return An empty territory vector since this player does not care for defense.
 */
unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toDefend() {
    return make_unique<vector<shared_ptr<Territory>>>();
}

// -- BENEVOLENT player strategy --
Benevolent::Benevolent(Player &player): PlayerStrategy(player) {}

void Benevolent::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toDefend() {

}

// -- NEUTRAL player strategy --
Neutral::Neutral(Player &player): PlayerStrategy(player) {}

void Neutral::issueOrder() {
    cout << "Neutral issueOrder()" << endl;
}

unique_ptr<vector<shared_ptr<Territory>>> Neutral::toAttack() {
    auto territories = make_unique<vector<shared_ptr<Territory>>>(*this->player->getTerritories());
    cout << "toAttack() Territories: " << endl;
    for (const auto& t : *territories) {
        cout << "\t" << *t << endl;
    }
    return territories;
}

unique_ptr<vector<shared_ptr<Territory>>> Neutral::toDefend() {
    auto territories = make_unique<vector<shared_ptr<Territory>>>(*this->player->getTerritories());
    cout << "toDefend() Territories: " << endl;
    for (const auto& t : *territories) {
        cout << "\t" << *t << endl;
    }
    return territories;
}

// -- CHEATER player strategy --
Cheater::Cheater(Player &player): PlayerStrategy(player) {}

void Cheater::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toDefend() {

}



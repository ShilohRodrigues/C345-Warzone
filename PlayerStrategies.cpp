#include "PlayerStrategies.h"

using namespace std;

// getters and setters
const shared_ptr<Player> &PlayerStrategy::getPlayer() const {
    return player;
}

void PlayerStrategy::setPlayer(shared_ptr<Player> &player) {
    PlayerStrategy::player = std::move(player);
}

// -- HUMAN player strategy --
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
void Aggressive::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Aggressive::toDefend() {

}

// -- BENEVOLENT player strategy --
void Benevolent::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Benevolent::toDefend() {

}

// -- NEUTRAL player strategy --
Neutral::Neutral(shared_ptr<Player> player) {
    this->setPlayer(player);
}

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
void Cheater::issueOrder() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toAttack() {

}

unique_ptr<vector<shared_ptr<Territory>>> Cheater::toDefend() {

}



#include "Cards.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include <random>
#include <chrono>

//---------------------------------------------------CARD---------------------------------------------------
// Default constructor
Card::Card() {

}
Card::Card(string *cardType): aCardType(cardType) {}
// Destructor
Card::~Card() {
	delete aCardType;
}
// Copy constructor
Card::Card(const Card& c)
{
	
}
// Assignment operator
Card& Card::operator=(const Card& c)
{
	this->cardsTypes = c.cardsTypes;
	this->aCardType = c.aCardType;
	return *this;
}
// stream insertion operator
ostream& operator<<(ostream& os, const Card& card) {
	os << card.getCardType();
	return os;
}
// Setter for the type of card
void Card::setCardType(int num)
{
	if (num >= 0 && num < cardsTypes.size()) {
		aCardType = &cardsTypes[num];
	}
	else {
		throw std::out_of_range("Invalid index for cardsTypes");
	}
}

// Getter for the type of card
const string& Card::getCardType() const
{
	return *aCardType;
}

void Card::setCardType(string *cardType) {
    Card::aCardType = cardType;
}

//---------------------------------------------------DECK---------------------------------------------------
// Default constructor
Deck::Deck()
{

}
// Destructor
Deck::~Deck()
{
	for (auto card : deck) {
		delete card;
	}
}
// Copy constructor
Deck::Deck(const Deck& d)
{
	this->deck = d.deck;
	this->card = d.card;

}
// stream insertion operator
ostream& operator<<(ostream& os, const Deck& deck) {
	for (const auto& card : deck.deck) {
		os << *card << " ";
	}
	return os;
}
// Assignment operator
Deck& Deck::operator=(const Deck& d)
{
	this->deck = d.deck;
	this->card = d.card;
	return *this;
}
// Make a deck of cards
void Deck::MakeDeck()
{
	srand(time(0));
	int i = rand() % 6 + 5;
	for (int n = 0; n < i; n++) {
		for (int j = 0; j < 6; j++)
		{
			card = new Card;
			card->setCardType(j);
			deck.push_back(card);
		}
	}
}
// Print the number of cards in the deck
void Deck::numOfCardsInDeck()
{
	cout << "\nNumber of Cards in Deck: " << deck.size() << endl;
}
// Draw a card from the deck
Card* Deck::draw()
{
	srand(time(NULL));
	int randomIndex = rand() % deck.size();
	card = deck.at(randomIndex);
	deck.erase(deck.begin() + randomIndex);
	return card;
}
// Add a card to the deck
void Deck::addCardToDeck(Card* one_card)
{
	deck.push_back(one_card);
}

//---------------------------------------------------HAND---------------------------------------------------
// Default constructor
Hand::Hand()
{

}
// Destructor
Hand::~Hand()
{
	for (auto card : handCards) {
		delete card;
	}
	for (auto card : playCards) {
		delete card;
	}
}
// Copy constructor
Hand::Hand(const Hand& h)
{
	this->handCards = h.handCards;
	this->playCards = h.playCards;
}
// Assignment operator
Hand& Hand::operator=(const Hand& h)
{
	this->handCards = h.handCards;
	this->playCards = h.playCards;
	return *this;
}
// stream insertion operator
ostream& operator<<(ostream& os, const Hand& hand) {
    os << "Hand cards: ";
	for (const auto& card : hand.handCards) {
		os << *card << " ";
	}

    os << "\nPlay cards: ";
    for (const auto& card : hand.playCards) {
        os << *card << " ";
    }
	return os;
}

// Setter for the hand of cards
void Hand::setHandOfCards(Card* a_card)
{
	handCards.push_back(a_card);

}
// Print the hand of cards
void Hand::printHandOfCards()
{
	cout << "Number of Cards on Hand: " << handCards.size() << endl;
	if (handCards.empty()) {
		cout << "\nThe Hand Cards is empty \n" << endl;
		return;
	}
	for (int j = 0; j < handCards.size(); j++) {
		cout << "Card No. " << j << " is " << handCards.at(j)->getCardType() << endl;
	}
}
// Print the play cards
void Hand::printPlayCards()
{
	if (playCards.size() > 0) {
		cout << "The Number of Play Cards: " << endl;
		for (int i = 0; i < playCards.size(); i++) {
			cout << "Card No. " << i << " is " << playCards.at(i)->getCardType() << endl;
		}
	}
	else {
		cout << "\nThere are no Play Cards\n" << endl;
	}
}
// Play: a card from the hand return to the deck
void Hand::play(Card* a_card, Deck* a_Deck)
{
	playCards.push_back(a_card);
	returnPlayedCardToDeck(a_Deck);
    deletePlayedCardFromHand(a_card);
}
// Return the played card to the deck
void Hand::returnPlayedCardToDeck(Deck* a_Deck)
{
	for (int n = 0; n < playCards.size(); n++) {
		a_Deck->addCardToDeck(playCards.at(n));
	}
}
// Getter for the hand of cards
vector<Card*>* Hand::getHandOfCards()
{
	return &handCards;
}
// Getter for the play cards
vector<Card*>* Hand::getPlayCards()
{
	return &playCards;
}
// Delete the played card from the hand
void Hand::deletePlayedCardFromHand(Card* r_card)
{
	// Iterate the elements of the handCards vector
	for (vector<Card*>::iterator it = handCards.begin(); it != handCards.end(); it++) {
		// Check if the type of the current card is the same as the type of the card to be deleted
		if ((*it)->getCardType() == r_card->getCardType()) {
			handCards.erase(it);
			cout << "Deleted " << r_card->getCardType() << " card from the Hand." << endl;
			break;
		}
	}
}

void Hand::deletePlayedCardFromPlayCards(const string& cardType) {
    for (auto it = playCards.begin(); it != playCards.end(); ++it) {
        if ((*it)->getCardType() == cardType) {
            // Remove the card from the playCards vector
            playCards.erase(it);
            cout << "Deleted " << cardType << " card from the playCards." << endl;
            return;
        }
    }
}
// Clear the play cards	
void Hand::clearPlayedCards()
{
	playCards.clear();
	cout << "\n Play Cards are Cleaned." << endl;
}

void Hand::addCardToHand(Card *card) {
    handCards.push_back(card);
}

void Hand::addCardToHand(const string& cardType) {
    auto* cardTypePtr = new string(cardType);
    Card* newCard = new Card(cardTypePtr);
    this->addCardToHand(newCard);
}

/**
 * Finds the first card in the hand or play cards matching the given card type.
 * @param handOrPlayCards handCards or playCards
 * @param cardType the type of the card
 * @return the index of the first matching card
 */
int Hand::findFirstCard(vector<Card *> *handOrPlayCards, const string& cardType) {
    for (int i = 0; i < handOrPlayCards->size(); i++) {
        if ((*handOrPlayCards)[i]->getCardType() == cardType) {
            // If we found a card with the specified type, return its index
            return i;
        }
    }

    // If we didn't find a card with the specified type, return -1 to indicate failure
    return -1;
}

Card* Hand::getCardFromHandCards(const string& cardType) {
    int cardIndex = Hand::findFirstCard(this->getHandOfCards(), cardType);
    auto card = *this->handCards[cardIndex];
    Card* cardPtr = &card;
    return cardPtr;
}

Card* Hand::getCardFromPlayCards(string cardType) {
    int cardIndex = Hand::findFirstCard(this->getPlayCards(), cardType);
    auto card = *this->handCards[cardIndex];
    Card* cardPtr = &card;
    return cardPtr;
}
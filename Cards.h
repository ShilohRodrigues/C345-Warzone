#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iterator>

using namespace std;

//---------------------------------------------------CARD---------------------------------------------------
class Card
{
public:
Card();
virtual ~Card();
Card(const Card& c);
Card& operator = (const Card& c);
void setCardType(int num);
const string& getCardType() const;
// stream insertion operator
friend ostream& operator<<(ostream& os, const Card& card);

private:
vector<string> cardsTypes = { "Spy", "Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy" };
string* aCardType = nullptr;
};
//---------------------------------------------------DECK---------------------------------------------------
class Deck
{
public:
	Deck();
	~Deck();
	Deck(const Deck& d);
	Deck& operator=(const Deck& d);
	void MakeDeck();
	void numOfCardsInDeck();
	Card* draw();
	void addCardToDeck(Card* one_card);
	// stream insertion operator
	friend ostream& operator<<(ostream& os, const Deck& deck);

private:
	vector<Card*> deck;
	Card* card;
};
//---------------------------------------------------HAND---------------------------------------------------
class Hand
{
public:
	Hand();
	~Hand();
	Hand(const Hand& h);
	Hand& operator=(const Hand& h);
	void setHandOfCards(Card* a_card);
	void printHandOfCards();
	void printPlayCards();
	void play(Card* a_card, Deck* a_Deck);
	void returnPlayedCardToDeck(Deck* a_Deck);
	vector<Card*>* getHandOfCards();
	vector<Card*>* getPlayCards();
	void deletePlayedCardsFromHand(Card* r_card);
	void clearPlayedCards();
	// stream insertion operator
	friend ostream& operator<<(ostream& os, const Hand& hand);

private:
	vector<Card*> handCards;
	vector<Card*> playCards;//for store play cards
};

void cardDemo1();

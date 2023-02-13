#include "Cards.h"

int main()
{
	cout << "The object is to create a hand object that is filled by drawing cards from deck. \n" << endl;
	// Create a deck of cards
	Deck* deck = new Deck;
	cout << "New Deck has made\n" << endl;
	deck->MakeDeck();
	// Create a hand of cards
	Hand* hand = new Hand;
	// Print the number of cards in the deck
	deck->numOfCardsInDeck();
	// Draw a card from the deck
	cout << "\nDrawing cards from the deck between 5 to 10 \n" << endl;
	int numOfCardsToDraw = 5 + rand() % 6;
	for (int i = 0; i < numOfCardsToDraw; i++)
	{
		hand->setHandOfCards(deck->draw());
	}
	// Print the number of cards in the deck
	hand->printHandOfCards();
	// Print the hand of cards
	deck->numOfCardsInDeck();
	// Play a card from the hand
	cout << "\nPlaying cards and then deleting it from hand\n" << endl;
	// Print the play cards
	int handCards = hand->getHandOfCards()->size();
	for (int i = 0; i < handCards; i++)
	{
		hand->play(hand->getHandOfCards()->at(0), deck);
	}
	// Print the hand of cards
	hand->printPlayCards();
	// Print the number of cards in the deck
	hand->printHandOfCards();
	cout << "\nAll cards return to the Deck \n" << endl;
	cout << "\nThe number of cards in the deck should be equal as initial state. \n" << endl;
	// Print the number of cards in the deck
	deck->numOfCardsInDeck();
	cout << "\nThe program successfully create a hand object that is filled by drawing cards from deck.\n" << endl;
}

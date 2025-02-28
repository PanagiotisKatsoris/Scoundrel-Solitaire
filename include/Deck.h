#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <unordered_set>
#include "CardAndDeckEnums.h"
#include "Card.h"


class Deck
{
    public:
        //constructs a standard deck of 52 playing cards
        Deck();
        virtual ~Deck();
        //iterates through the array and prints every single card. this is used to check if the constructor worked properly
        void PrintDeck();
        //returns a random card from the deck and also checks if that card has been drawn before to avoid duplicate draws
        Card DrawCard();
        //resets the unordered set which is used to check which cards have been drawn essentially allowing the DrawCard() method to draw any card again
        void ResetDeck();
    protected:

    private:
        //array of type Card to hold each different card. currently this is like a template and no insertions or deletions occur
        Card deckarr[52];
        //set of numbers holding the position in the deckarr array of each card that is being drawn with the DrawCard() method which is used to avoid duplicate draws
        std::unordered_set<int> cardsdrawn;
};

#endif // DECK_H

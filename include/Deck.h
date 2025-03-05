#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <unordered_set>
#include "CardAndDeckEnums.h"
#include "Card.h"


class Deck
{
    public:
        /*
        default constructor constructs a standard deck of 52 playing cards
        destructor destructs it
        PrintDeck() prints in sequence all cards of the deck
        DrawCard() has a default function to draw a random card from the deck and return it also removing it from the pool of cards able to be drawn, or takes an argument and does the same for a specific card
        ResetDeck() resets the number of cards drawn to 0
        */
        Deck();
        virtual ~Deck();
        void PrintDeck();
        Card DrawCard();
        Card DrawCard(int specific);
        void ResetDeck();
    protected:

    private:
        //array of type Card to hold each different card. currently this is like a template and no insertions or deletions occur
        Card deckarr[52];
        //set of numbers holding the position in the deckarr array of each card that is being drawn with the DrawCard() method which is used to avoid duplicate draws
        std::unordered_set<int> cardsdrawn;
        Card null;
};

#endif // DECK_H

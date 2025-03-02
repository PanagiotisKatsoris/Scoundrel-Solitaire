#ifndef CARD_H
#define CARD_H
#include <iostream>
#include "CardAndDeckEnums.h"
#include <string>


class Card
{
    public:
        //one constructor creates a specific card of rank and suit which are enums in the cardanddeckenums header file. the other constructor creates a null card
        Card(Rank r, Suit s);
        Card();
        virtual ~Card();
        //SetRank and SetSuit set a card's rank and suit respectively to a given rank or suit
        void SetRank(Rank r);
        void SetSuit(Suit s);
        //GetRank and GetSuit respectively return a card's rank and suit
        Rank GetRank() const;
        Suit GetSuit() const;
        //prints card in "Rank of Suit" format if its a card or "Empty" if its a null card
        void PrintCard();
        //returns a string in format "Rank of Suit" of the card or "Empty" if card is null
        std::string CardToString();

    protected:

    private:
        //rank and suit variable for each card
        Rank rank;
        Suit suit;
};

#endif // CARD_H

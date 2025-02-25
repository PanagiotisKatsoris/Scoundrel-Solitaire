#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include "CardAndDeckEnums.h"


class Card
{
    public:
        Card(Rank r, Suit s);
        Card();
        virtual ~Card();

        void SetRank(Rank r);
        void SetSuit(Suit s);
        Rank GetRank() const;
        Suit GetSuit() const;
        void PrintCard();

    protected:

    private:
        Rank rank;
        Suit suit;
};

#endif // CARD_H

#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <string>
#include "CardAndDeckEnums.h"
#include "Card.h"


class Deck
{
    public:
        Deck();
        virtual ~Deck();

        void PrintDeck();
        Card DrawCard();
    protected:

    private:
        Card deckarr[52];
};

#endif // DECK_H

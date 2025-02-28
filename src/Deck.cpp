#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Card.h"
#include <iostream>
#include <time.h>
#include <unordered_set>
#include <climits>

Deck::Deck()
{
    for (int row = CLUBS; row <= SPADES; row++)
    {
        for (int col = ACE; col <= KING; col++)
        {
            int pos = (row*13)+(col-1);
            Suit tempenums = static_cast<Suit>(row);
            Rank tempenumr = static_cast<Rank>(col);
            deckarr[pos]=Card(tempenumr, tempenums);
        }
    }
}

Deck::~Deck()
{
    //dtor
}


void Deck::PrintDeck()
{
    for (int i = 0; i <52; i++)
    {
        deckarr[i].PrintCard();
        if ((i+1)%13 == 0)
        {
            std::cout<<"------------------------"<<std::endl;
        }
    }
}

Card Deck::DrawCard()
{
    srand(time(NULL));
    unsigned long seed = rand()%ULONG_MAX;
    srand(seed);
    int randcard = rand()%51;
    while (cardsdrawn.find(randcard) != cardsdrawn.end())
    {
        randcard = rand()%51;
    }
    cardsdrawn.insert(randcard);
    return deckarr[randcard];
}

void Deck::ResetDeck()
{
    cardsdrawn.clear();
}

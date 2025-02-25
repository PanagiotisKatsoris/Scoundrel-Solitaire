#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <time.h>

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
    int seed = rand()%52525252;
    srand(seed);
    int randcard = rand()%51;
    return deckarr[randcard];
}

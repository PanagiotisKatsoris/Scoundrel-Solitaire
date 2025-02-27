#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

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
    unsigned long seed = rand()%52525252;
    srand(seed);
    int randcard = rand()%51;
    if (!cardsdrawn.empty())
    {
        bool dupe = true;
        do
        {
          for (const int& i : cardsdrawn)
          {
              if(cardsdrawn.at(i)==randcard)
              {
                  randcard = rand()%51;
                  break;
              }
              else if (i==(cardsdrawn.size()-1))
              {
                  dupe = false;
                  break;
              }
          }
        }
        while (dupe);
    }
    else
    {
        cardsdrawn.push_back(randcard);
    }
    return deckarr[randcard];
}

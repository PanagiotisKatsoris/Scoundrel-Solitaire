#include "Card.h"
#include "CardAndDeckEnums.h"
#include <iostream>
#include <string>

Card::Card()
{
    //ctor
}

Card::~Card()
{
    //dtor
}

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Rank Card::GetRank() const
{
    return rank;
}

Suit Card::GetSuit() const
{
    return suit;
}
void Card::PrintCard()
{
    std::string str;
    std::string stringRank;
    std::string stringSuit;

    switch(rank)
    {
    case 1:
        stringRank = "Ace";
        break;
    case 2:
        stringRank = "Two";
        break;
    case 3:
        stringRank = "Three";
        break;
    case 4:
        stringRank = "Four";
        break;
    case 5:
        stringRank = "Five";
        break;
    case 6:
        stringRank = "Six";
        break;
    case 7:
        stringRank = "Seven";
        break;
    case 8:
        stringRank = "Eight";
        break;
    case 9 :
        stringRank = "Nine";
        break;
    case 10:
        stringRank = "Ten";
        break;
    case 11:
        stringRank = "Jack";
        break;
    case 12:
        stringRank = "Queen";
        break;
    case 13:
        stringRank = "King";
        break;
    default:
        stringRank = "Rank Error";
    }
    switch(suit)
    {
    case 0:
        stringSuit = "Clubs";
        break;
    case 1:
        stringSuit = "Diamonds";
        break;
    case 2:
        stringSuit = "Hearts";
        break;
    case 3:
        stringSuit = "Spades";
        break;
    default :
        stringSuit = "Suit Error";
    }
    str = stringRank + " of " + stringSuit;
    std::cout<<str<<std::endl;
}

void Card::SetRank(Rank r)
{
    rank = r;
}

void Card::SetSuit(Suit s)
{
    suit = s;
}

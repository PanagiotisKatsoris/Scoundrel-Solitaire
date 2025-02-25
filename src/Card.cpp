#include "Card.h"
#include "CardAndDeckEnums.h"
#include <iostream>
#include <string>

Card::Card() : rank(NULLRANK), suit(NULLSUIT)
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
//checks the rank then suit of card and prints it. in case either is missing it prints "empty"
//which will be useful to appear when a card is removed from a spot in the room while playing
void Card::PrintCard()
{
    std::string str;
    std::string stringRank;
    std::string stringSuit;
    bool isCard=true;

    switch(rank)
    {
    case 1:
        stringRank = "Ace";
        str = stringRank + " of ";
        break;
    case 2:
        stringRank = "Two";
        str = stringRank + " of ";
        break;
    case 3:
        stringRank = "Three";
        str = stringRank + " of ";
        break;
    case 4:
        stringRank = "Four";
        str = stringRank + " of ";
        break;
    case 5:
        stringRank = "Five";
        str = stringRank + " of ";
        break;
    case 6:
        stringRank = "Six";
        str = stringRank + " of ";
        break;
    case 7:
        stringRank = "Seven";
        str = stringRank + " of ";
        break;
    case 8:
        stringRank = "Eight";
        str = stringRank + " of ";
        break;
    case 9 :
        stringRank = "Nine";
        str = stringRank + " of ";
        break;
    case 10:
        stringRank = "Ten";
        str = stringRank + " of ";
        break;
    case 11:
        stringRank = "Jack";
        str = stringRank + " of ";
        break;
    case 12:
        stringRank = "Queen";
        str = stringRank + " of ";
        break;
    case 13:
        stringRank = "King";
        str = stringRank + " of ";
        break;
    case 14:
        str = "Empty";
        isCard = false;
        break;
    default:
        str = "Empty";
        isCard = false;
    }
    if (isCard){
        switch(suit)
        {
        case 0:
            stringSuit = "Clubs";
            str.append(stringSuit);
            break;
        case 1:
            stringSuit = "Diamonds";
            str.append(stringSuit);
            break;
        case 2:
            stringSuit = "Hearts";
            str.append(stringSuit);
            break;
        case 3:
            stringSuit = "Spades";
            str.append(stringSuit);
            break;
        case 4:
            str = "Empty";
            break;
        default :
            str = "Empty";
        }
    }
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

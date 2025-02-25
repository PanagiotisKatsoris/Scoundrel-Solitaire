#include <iostream>
#include <string>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"

/*
version 0.1
this current build only creates a deck of 52 cards and it runs a simple test to check if it works properly
*/

int main()
{
    Card* testcard = new Card(TWO, SPADES);
    testcard->PrintCard();
    std::cout<<std::endl;
    Deck myDeck;
    myDeck.PrintDeck();
    return 0;
}

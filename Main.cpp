#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Game.h"

/*
version 0.1
this current build only creates a deck of 52 cards and it runs a simple test to check if it works properly
*/

int main()
{
    Game play;
    Deck myDeck;
    Card temp;
    temp.PrintCard();
    temp = myDeck.DrawCard();
    temp.PrintCard();


    return 0;
}

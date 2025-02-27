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
TODO
make card draw for game that uses cardaw of deck but also checks within it the cards drawn already.
use that in the dealspot which deals one spot of room which is then used in the dealroom which checks size of cards drawn.
way to iterate vetor and compare with array to check which cards are drawn and have each card be drawn only once.
very later stage to RUN FRoM ROOM.
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

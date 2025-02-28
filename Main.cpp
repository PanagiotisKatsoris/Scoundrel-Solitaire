#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Game.h"

/*
version 0.2
-------------------------------------------------------------
method and variable explanation exists mostly in header files
-------------------------------------------------------------
Current version creates a deck of 52 playing cards. Creates a player with 20 hp, a room with 4 spots and can manipulate player's hp and deal new cards in room
TODO
documentation


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

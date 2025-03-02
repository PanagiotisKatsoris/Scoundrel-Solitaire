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


very later stage to RUN FRoM ROOM. this will be Teleport away and
will use a second deck that stores rooms which have been teleported
away from and starts being dealt after the initial deck is empty
*/

int main()
{
    Game play;
    play.DealRoom();
    play.PrintRoom();
    std::cout<<"ey yo u got "<<play.GetHp()<<" hp and weapon slot is currently "<<(play.GetWeapon()).CardToString()<<std::endl;
    play.EmptyRoom();
    play.DealRoom();
    play.PrintRoom();
    for(int i = 0; i<10; i++)
    {
        play.EmptyRoom();
        play.DealRoom();
    }
    play.PrintRoom();
    play.EmptyRoom();
    play.PrintRoom();
    play.PrintRoom();
    play.DealRoom();
    play.PrintRoom();
    return 0;
}

#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Game.h"
#include <cstdlib>

/*
version 0.3
-------------------------------------------------------------
method and variable explanation exists mostly in header files
-------------------------------------------------------------
Current version creates a deck of 52 playing cards. Creates a player with 20 hp, a room with 4 spots and can manipulate player's hp and deal new cards in room
TODO
documentation

idlestate function which is normal state where screen is cleared and room is printed alongside stats
values for each card so for monsters it becomes damage, potions becomes heal, weapon is subtracted from monster damage.
game mode basic should not include face cards and aces of diamonds and hearts
add choice for modules: face cards of diamonds are blacksmiths, hearts are fairies. maybe a module with jokers(maybe they are double edged swords that either help or hinder the player)
secondary deck which might be a vector or something to add cards from teleport function
if secondary deck is not empty then dealroom will continue drawing from that if original deck is emptied
check possible bug if deck runs out while dealing room mid-room
define controls(check comment at bottom)
add quit game function
add restart game
add prologue to game
add how to play section, could be shown or skipped
add guide of card values

dealt with bug of deck not drawing king of spades and infinitely looping

very later stage to RUN FRoM ROOM. this will be Teleport away and
will use a second deck that stores rooms which have been teleported
away from and starts being dealt after the initial deck is empty
*/
//--------------BELOW THIS LINE IS THE DECLARATION OF FUNCTIONS--------------------
void clearScreen()//i did not declare and then define this one i know.
{
    #ifdef _WIN32
        system("cls"); //if in Windows
    #else
        system("clear");//if in Linux or macOS
    #endif
}
//this is a test function to see how it works
void testit(Game play);
//---------------BELOW THIS LINE IS THE MAIN FUNCTION ---------------
int main()
{
    Game play;
    testit(play);


    return 0;
}
/*   BELOW THIS LINE ARE THE DEFINITIONS OF FUNCTIONS
-------------------------------------------------------------*/

void testit(Game play)
{
    play.PrintGameDeck();
}
// --------- BELOW THIS LINE ARE THE CONTROLS-------------------
/*
h=show controls
1=choose first spot of room , if spot was empty return to idle
2=choose second spot...
3=choose third...
4=choose fourth...
y=accept, forward with code
c=cancel, returns to idle
q=quit program
r=reset game, or restart game.
t=teleport away from room
g=show guide for card values
s=show current stats, either includes weapkills or thats different checkweapon control, will decide later
maybe a control to show the how-to-play section?
*/

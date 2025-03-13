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

ordering of methods in Game class.better organization and grouping for better readability.
idlestate function which is normal state where screen is cleared and room is printed alongside stats
values for each card so for monsters it becomes damage, potions becomes heal, weapon is subtracted from monster damage.
game mode basic should not include face cards and aces of diamonds and hearts
add choice for modules: face cards of diamonds are blacksmiths, hearts are fairies. maybe a module with jokers(maybe they are double edged swords that either help or hinder the player)
secondary deck which might be a vector or something to add cards from teleport function
if secondary deck is not empty then dealroom will continue drawing from that if original deck is emptied
define controls(check comment at bottom)
add quit game function
add restart game--debatable--
add prologue to game
add how to play section, could be shown or skipped
add guide of card values


very later stage to RUN FRoM ROOM. this will be Teleport away and
will use a second deck that stores rooms which have been teleported
away from and starts being dealt after the initial deck is empty
*/
//--------------BELOW THIS LINE IS THE DECLARATION OF VARIABLES--------------------
int progress;
short realspot;
short weaponvalue;
//--------------BELOW THIS LINE IS THE DECLARATION OF FUNCTIONS--------------------
void clearScreen()// this is used for cleaner approach with the game. clears terminal clutter.
{
    #ifdef _WIN32
        system("cls"); //if in Windows
    #else
        system("clear");//if in Linux or macOS
    #endif
}
/*

OpenState is the default idle state of the game. when called prints room, stats and waits for input.
NewState is used to clear a room after an action then proceed to OpenState.
*/

void OpenState(Game& play);
void NewState(Game& play, short clearroom);
void AskInput();
void InputCheck(char in);//calls method based on input. if input is room spot it calls pickcard
void PickCard(short spotpicked);

short MonVal(Rank rr);
short HeartVal(Rank rr);
short DiaVal(Rank rr);
void FistFight(Game& play, short value);
void WeaponFight(Game& play, short value);
void Fight(Game& play, Card cc);


//---------------BELOW THIS LINE IS THE MAIN FUNCTION ---------------
int main()
{
    Game play;
    progress = 0;
    OpenState(play);
    play.EmptyRoom();
    play.PrintRoom();
    OpenState(play);


    return 0;
}
/*   BELOW THIS LINE ARE THE DEFINITIONS OF FUNCTIONS
-------------------------------------------------------------*/


void OpenState(Game& play)
{
    //clearScreen();-------------------------------temporarily disabled for testing purposes.
    int nullcounter = 0;
    for (int roomcounter = 0; roomcounter <4; roomcounter++)
    {
        switch((play.GetSpot(roomcounter)).GetSuit())
        {
        case 4:
            nullcounter++;
            break;
        }
    }
    if(nullcounter>=3)
    {
        play.DealRoom();
    }
    play.PrintRoom();
    play.PrintStats();
    std::cout<<"(Type h to see all controls)\nPick a card: ";
}

void NewState(Game& play, short clearroom)
{
    play.EmptySpot(clearroom);
    OpenState(play);
}

short MonVal(Rank rr)
{
    switch(rr)
    {
    case 1:
        return 14;
    case 14:
        return 0;
    default :
        return static_cast<short>(rr);
    }
}
void FistFight(Game& play, short value)
{
    std::cout<<"You fight the monster with your fist. You take "<<-value<<" points of damage and slay the monster.\n";
    play.SetHp(value);
    play.PrintStats();
    std::cout<<"\nPress Enter to continue...";
    std::cin.ignore();
    NewState(play, realspot);
}
void WeaponFight(Game& play, short value)
{
    short diff = weaponvalue + value;
    if (diff>=0)
    {
        diff = 0;
    }
    std::cout<<"You fight the monster with your weapon. You take "<<-diff<<" points of damage and slay the monster. The monster curses your weapon.\n";
    play.SetHp(diff);
    play.PrintStats();
    std::cout<<"\nPress Enter to continue...";
    std::cin.ignore();
    NewState(play, realspot);
}
void Fight(Game& play, Card cc)
{
    short value = -MonVal(cc.GetRank());
    if (play.CheckWeapHeld() && play.KillsExist())
    {

    }
    else if (play.CheckWeapHeld() && !play.KillsExist())
    {
        std::cout<<"Fight this monster with your weapon?  Enter c to use your fists instead ";//-------------continue here plz
    }
    else
    {
        FistFight(play, value);
    }


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

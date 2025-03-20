#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include "Game.h"
#include <cstdlib>
#include <set>
#include <limits>
/*
version 0.4.2
-------------------------------------------------------------
method and variable explanation exists mostly in header files
-------------------------------------------------------------
Current version creates a deck of 52 playing cards. Creates a player with 20 hp, a room with 4 spots and can manipulate player's hp and deal new cards in room

TODO
documentation

ordering of methods in Game class.better organization and grouping for better readability.
game mode basic should not include face cards and aces of diamonds and hearts
add choice for modules: face cards of diamonds are blacksmiths, hearts are fairies. maybe a module with jokers(maybe they are double edged swords that either help or hinder the player)
secondary deck which might be a vector or something to add cards from teleport function
if secondary deck is not empty then dealroom will continue drawing from that if original deck is emptied
define controls(check comment at bottom)
add restart game--debatable--
add prologue to game
add how to play section, could be shown or skipped
add guide of card values


very later stage to RUN FRoM ROOM. this will be Teleport away and
will use a second deck that stores rooms which have been teleported
away from and starts being dealt after the initial deck is empty
*/
//--------------BELOW THIS LINE IS THE DECLARATION OF VARIABLES--------------------
/*
progress counts how many monsters are slain and when it reaches 26 with hp>0 it gives victory screen
realspot is a short that converts the input of a spot chosen in room during picking card phase into the internal number of the real position
weaponvalue stores the value of held weapon for easier access
cinput stores the input of the player which is a char
acceptedanswers is a set that holds the accepted values of input
token is a temporary card which will hold the selected card each time a card is picked for easier access to it
*/
int progress;
short realspot;
short weaponvalue = 0;
char cinput;
std::unordered_set<char> acceptedanswers = {'1', '2', '3', '4', 'y', 'c', 'h', 't', 'g', 's', 'q', 'f'};
Card token;
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
Quit reduces hp to 0 thus exiting the loop and quitting the program.
OpenState is the default idle state of the game. when called prints room, stats and waits for input.
NewState is used to clear a room after an action then proceed to OpenState.
AskInput()
InputCheck()
PickCard()

MonVal returns a short based on value of monster determined by its rank.
HeartVal()
DiaVal()
FistFight deals damage to hp based on monster value, empties room spot
WeaponFight calculates damage based on weapon value and monster value, deals damage to hp, empties room spot
Fight asks user if they wish to fight. choice between using weapon and fists. if weapon is chosen but condition to fight are not met, fists are used instead. always cancellable. calls correct fight function based on case

*/

void Quit(Game& play);
void ClearBuffer();
void EnterToContinue();

void OpenState(Game& play);
void NewState(Game& play, short clearroom);
void AskInput();
void InputCheck(Game& play);//calls method based on input. if input is room spot it calls pickcard
void PickCard(Game& play, short spotpicked);

short MonVal(Rank rr);
short HeartVal(Rank rr);
short DiaVal(Rank rr);
void FistFight(Game& play, short value);
void WeaponFight(Game& play, short value);
void Fight(Game& play, Card cc);
void Heal(Game& play, Card cc);


//---------------BELOW THIS LINE IS THE MAIN FUNCTION ---------------
int main()
{
    Game play;
    progress = 0;
    Card testt(THREE, HEARTS);
    Card testtt(SIX, CLUBS);
    //here is where the intro comes in
    //choice for how to play section or skip straight to starting the game
    //choice for mode. base/blacksmiths/fairies
    //final words, objective and good luck!
    OpenState(play);
    do
    {
        //here is where game will take place
        AskInput();
        InputCheck(play);
    } while (play.GetHp()>0);
    std::cout<<"PLACEHOLDER->You couldn't survive the dungeon. Someone else might have a chance because of you and thus your soul rests in peace...";
    EnterToContinue();


    return 0;
}
/*   BELOW THIS LINE ARE THE DEFINITIONS OF FUNCTIONS
-------------------------------------------------------------*/

void Quit(Game& play)
{
    play.SetHp(-20);
}
void ClearBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void EnterToContinue()
{
    std::cout<<"\nPress Enter to continue..."<<std::endl;
    std::cin.get();
}

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
    std::cout<<""<<std::endl;
    play.PrintRoom();
    play.PrintStats();
    std::cout<<"(Type h to see all controls)\nPick a card: ";
}

void NewState(Game& play, short clearroom)
{
    play.EmptySpot(clearroom);
    OpenState(play);
}
void PickCard(Game& play, short spotpicked)
{
    realspot = spotpicked - 1;
    token = play.GetSpot(realspot);
    switch(token.GetSuit())
    {
    case NULLSUIT:
        std::cout<<"This spot is empty. Please pick a spot with a card.\n";
        OpenState(play);
        break;
    case SPADES:
    case CLUBS:
        std::cout<<"You picked "<<token.CardToString()<<std::endl;
        Fight(play, token);
        break;
    case HEARTS:
        std::cout<<"You picked "<<token.CardToString()<<std::endl;
        Heal(play, token);
        //heal() for heals 2-10 and ace. healfay() for jack queen king. use switch statement here
        break;
    case DIAMONDS:
        std::cout<<"You picked "<<token.CardToString()<<std::endl;
        //equip() for 2-10. forge() for jack queen king ace. use switch statement here
        break;
    default :
        std::cout<<"Some kind of error has occurred. Please report this bug...";
        EnterToContinue();
        break;
    }
}
void AskInput()
{
    while (true)
    {
        std::cin>>std::ws;
        std::cin.get(cinput);
        ClearBuffer();
        if (std::cin.fail())
        {
            std::cin.clear();
            ClearBuffer();
            std::cout<<"\nMajor Error. Not a valid input. Please enter a valid character. Press h for a list of controls ... ";
        }
        else if (acceptedanswers.find(cinput)!=acceptedanswers.end())
        {
            break;
        }
        else if (acceptedanswers.find(cinput)==acceptedanswers.end())
        {
            std::cout<<"\nError. Not a valid input. Please enter a valid character. Press h for a list of controls ... ";
            continue;
        }
        else
        {
            std::cout<<"\nUnhandled Error. Not a valid input. Please enter a valid character. Press h for a list of controls ... ";
            continue;
        }

    }
}
void InputCheck(Game& play)
{
    switch(cinput)
    {
    case '1':
        PickCard(play, 1);
        break;
    case '2':
        PickCard(play, 2);
        break;
    case '3':
        PickCard(play, 3);
        break;
    case '4':
        PickCard(play, 4);
        break;
    default :
        std::cout<<"You failed to pick a card. "<<std::endl;
        OpenState(play);
        break;
    }
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
short HeartVal(Rank rr)
{
    switch(rr)
    {
    case 1:
        return 20;
    case 11:
        return 1;
    case 12:
        return 2;
    case 13:
        return 3;
    default :
        return static_cast<short>(rr);
    }
}
short DiaVal(Rank rr)
{
    switch(rr)
    {
    case 1:
        return 13;
    case 11:
        return 1;
    case 12:
        return 2;
    case 13:
        return 3;
    default :
        return static_cast<short>(rr);
    }
}
void FistFight(Game& play, short value)
{
    std::cout<<"You fight the monster with your fist. You take "<<-value<<" points of damage and slay the monster.\n";
    play.SetHp(value);
    play.PrintStats();
    progress++;
    EnterToContinue();
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
    play.AddKill(-value);
    play.PrintStats();
    progress++;
    EnterToContinue();
    NewState(play, realspot);
}
void Fight(Game& play, Card cc)
{
    short value = -MonVal(cc.GetRank());
    if (play.CheckWeapHeld() && play.KillsExist())
    {
        short lastkill = play.GetLastKill();
        short comparekill = lastkill + value;
        if (comparekill>0)
        {
        std::cout<<"A monster stands in your way. Enter y to use your weapon or f to use your fists ";
        AskInput();
        switch (cinput)
            {
            case 'f':
                FistFight(play, value);
                break;
            case 'q':
                Quit(play);
                break;
            case 'c':
                OpenState(play);
                break;
            default:
                WeaponFight(play, value);
                break;
            }
        }
        else
        {
            std::cout<<"The last monster you have slain cursed your sword with its value of "<<lastkill<<". You can not use this weapon to fight a monster with an equal or higher value than that. \nEnter f to use your fists instead or c to cancel and go back ";
            AskInput();
            switch (cinput)
            {
            case 'f':
                FistFight(play, value);
                break;
            case 'q':
                Quit(play);
                break;
            case 'c':
                OpenState(play);
                break;
            default:
                OpenState(play);
                break;
            }
        }
    }
    else if (play.CheckWeapHeld() && !play.KillsExist())
    {
        std::cout<<"A monster stands in your way. Enter y to use your weapon or f to use your fists ";
        AskInput();
        switch (cinput)
        {
        case 'f':
            FistFight(play, value);
            break;
        case 'q':
            Quit(play);
            break;
        case 'c':
            OpenState(play);
            break;
        default:
            WeaponFight(play, value);
            break;
        }
    }
    else
    {
        FistFight(play, value);
    }


}
void Heal(Game& play, Card cc)
{
    short healvalue = HeartVal(cc.GetRank());
    std::cout<<"You found a potion! Heal your hp? Press y to heal or c to Cancel... ";
    AskInput();
    switch(cinput)
    {
    case 'q':
        Quit(play);
        break;
    case 'c':
        OpenState(play);
        break;
    case 'y':
    default :
        std::cout<<"The potion invigorates you. HP healed.\n";
        play.SetHp(healvalue);
        play.PrintStats();
        EnterToContinue();
        NewState(play, realspot);
        break;
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

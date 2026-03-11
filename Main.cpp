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
#include <deque>
/*
version 0.4.5
-------------------------------------------------------------
method and variable explanation exists mostly in header files
-------------------------------------------------------------
Current version creates a deck of 52 playing cards. Creates a player with 20 hp, a room with 4 spots and can manipulate player's hp and deal new cards in room

TODO
documentation

visibility on number of kills on a weapon
define controls(check comment at bottom)
add restart game--debatable--
add prologue to game
add how to play section, could be shown or skipped
add guide of card values

*/
//--------------BELOW THIS LINE IS THE DECLARATION OF VARIABLES--------------------
/*
progress counts how many monsters are slain and when it reaches 26 with hp>0 it gives victory screen
realspot is the real value of the position in the array that represent spots in the room of the card chosen. conversion from what the user typed to what the real value is happens in PickCard()
weaponvalue stores the value of held weapon for easier access
cinput stores the input of the player which is of type char
acceptedanswers is a set that holds the accepted values of input
token is a temporary card which will hold the selected card each time a card is picked for easier access to it
roomfull is a boolean initialized to true, if empty spots exist it sets to false until new room is dealt
notp is a boolean initialized to false. if teleport is used it will set to true and subsequent teleport will be disabled. when a new card is played from the new room it will set to false again
expansion is a boolean which is set true until an game mode is selected either with or without expansions which is then set to false so game can start
*/
int progress;
short realspot;
short weaponvalue = 0;
char cinput;
std::unordered_set<char> acceptedanswers = {'1', '2', '3', '4', 'c', 'f', 'g', 'h', 'n', 'q', 's', 't', 'y'};
Card token;
bool roomfull = true;
bool notp = false;
bool expansion = true;
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
NewState is used to clear a room after an action.
PickCard checks card at selected spot of room and proceed to correct function based on card chosen. if spot is empty does nothing
AskInput waits for input from user and if it is an accepted input proceeds to inputcheck() otherwise keeps aksing for input.
InputCheck checks case to handle depending on input.
ExpansionCheck asks for input and chooses which expansions to be included by removing the appropirate cards from the deck in each case

MonVal returns a short based on value of monster determined by its rank.
HeartVal returns a short based on value of potion or fairy (hearts face cards)
DiaVal returns a short based on value of weapon or how much it forges if blacksmith card (diamond face cards)
FistFight deals damage to hp based on monster value, empties room spot
WeaponFight calculates damage based on weapon value and monster value, deals damage to hp, empties room spot
Fight asks user if they wish to fight. choice between using weapon and fists. if weapon is chosen but condition to fight are not met, fists are used instead. always cancellable. calls correct fight function based on case
Heal heals user hp with potion chosen
HealFay heals user hp based on number of kills (weapkills size) on their weapon and the value of face card or 20 hp with ace card
Equip either changes weapon to selected card or discards selected card
Forge removes values from lowest to higher from the weapkills set essentially allowing a weapon to reach a previous state of what power level of monsters it can kill
TpAway at the start of the room and also not directly after this has been used again, removes all 4 cards and places them at the end of the dungeon to be faced at a later time
*/

void Quit(Game& play);
void ClearBuffer();
void EnterToContinue();

void OpenState(Game& play);
void NewState(Game& play, short clearroom);
void PickCard(Game& play, short spotpicked);
void AskInput();
void InputCheck(Game& play);
void ExpansionCheck(Game& play);


short MonVal(Rank rr);
short HeartVal(Rank rr);
short DiaVal(Rank rr);
void FistFight(Game& play, short value);
void WeaponFight(Game& play, short value);
void Fight(Game& play, Card cc);
void Heal(Game& play, Card cc);
void HealFay(Game& play, Card cc);
void Equip(Game& play, Card cc);
void Forge(Game& play, Card cc);
void TpAway(Game& play);

//---------------BELOW THIS LINE IS THE MAIN FUNCTION ---------------
int main()
{
    Game play;
    progress = 0;
    //here is where the intro comes in
    //final words, objective and good luck!
    do
    {
        ExpansionCheck(play);
    } while (expansion);

    do
    {
        if (progress>=26)
        {
            clearScreen();
            std::cout<<"PLACEHOLDER--> YOU WIN !!! gzzz"<<std::endl;
            return 0;
        }
        OpenState(play);
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
    clearScreen();
    int nullcounter = 0;
    roomfull = false;
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
        roomfull=true;
    }
    std::cout<<""<<std::endl;
    play.PrintRoom();
    if (roomfull==true)
    {
        std::cout<<"### You Enter A New Room ###\n-----------------------------------"<<std::endl;
    }
    play.PrintStats();
    std::cout<<"-----------------------------------\n(Type h to see all controls)\nPick a card: ";
}
void NewState(Game& play, short clearroom)
{
    play.EmptySpot(clearroom);
    notp=false;
}
void PickCard(Game& play, short spotpicked)
{
    realspot = spotpicked - 1;
    token = play.GetSpot(realspot);
    switch(token.GetSuit())
    {
    case NULLSUIT:
        std::cout<<"This spot is empty. Please pick a spot with a card.\n";
        EnterToContinue();
        return;
    case SPADES:
    case CLUBS:
        std::cout<<"You picked "<<token.CardToString()<<"\n-----------------------------------"<<std::endl;
        Fight(play, token);
        return;
    case HEARTS:
        std::cout<<"You picked "<<token.CardToString()<<"\n-----------------------------------"<<std::endl;
        switch (token.GetRank())
        {
        case ACE:
        case JACK:
        case QUEEN:
        case KING:
            HealFay(play, token);
            return;
        default :
            Heal(play, token);
            return;
        }
        return;
    case DIAMONDS:
        std::cout<<"You picked "<<token.CardToString()<<"\n-----------------------------------"<<std::endl;
        switch(token.GetRank())
        {
        case ACE:
        case JACK:
        case QUEEN:
        case KING:
            Forge(play, token);
            return;
        default:
            Equip(play, token);
            return;
        }
        return;
    default :
        std::cout<<"Some kind of error has occurred. Please report this bug...";
        EnterToContinue();
        return;
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
            return;
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
        return;
    case '2':
        PickCard(play, 2);
        return;
    case '3':
        PickCard(play, 3);
        return;
    case '4':
        PickCard(play, 4);
        return;
    case 't':
        TpAway(play);
        return;
    default :
        std::cout<<"You failed to choose a correct action! "<<std::endl;
        EnterToContinue();
        return;
    }
}
void ExpansionCheck(Game& play)
{
    clearScreen();
    std::cout<<"Before proceeding you should choose a game mode.\nType 1 to select the Base Game mode with only the basic cards and rules\nType 2 to add the Healing Fairies expansion to the base game\nType 3 to add the Forging Fairies expansion to the base game\nType 4 to add all expansions to the base game and play the Full Game mode\nYour choice : ";
    AskInput();
    switch(cinput)
    {
        case '1':
            play.RemoveDiamonds();
            play.RemoveHearts();
            expansion=false;
            std::cout<<"Proceeding to Base Game... "<<std::endl;
            EnterToContinue();
            break;
        case '2':
            play.RemoveDiamonds();
            expansion=false;
            std::cout<<"Proceeding to Base Game with Healing fairies expansion... "<<std::endl;
            EnterToContinue();
            break;
        case '3':
            play.RemoveHearts();
            expansion=false;
            std::cout<<"Proceeding to Base Game with Forging Fairies expansion... "<<std::endl;
            EnterToContinue();
            break;
        case '4':
            expansion=false;
            std::cout<<"Proceeding to Full Game...\nAll expansions added... "<<std::endl;
            EnterToContinue();
            break;
        default :
            std::cout<<"Invalid Input. Try Again"<<std:endl;
            EnterToContinue();
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
    std::cout<<"-----------------------------------"<<std::endl;
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
    std::cout<<"-----------------------------------"<<std::endl;
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
                return;
            case 'q':
                Quit(play);
                return;
            case 'c':
                return;
            case 'y':
                WeaponFight(play, value);
                return;
            default:
                std::cout<<"Something went wrong. Check your inputs."<<std::endl;
                EnterToContinue();
                return;
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
                return;
            case 'q':
                Quit(play);
                return;
            case 'c':
                return;
            default:
                return;
            }
        }
    }
    else if (play.CheckWeapHeld() && !play.KillsExist())
    {
        std::cout<<"A monster stands in your way. Press y to use your weapon or f to use your fists ";
        AskInput();
        switch (cinput)
        {
        case 'f':
            FistFight(play, value);
            return;
        case 'q':
            Quit(play);
            return;
        case 'c':
            return;
        case 'y':
            WeaponFight(play, value);
            return;
        default:
            std::cout<<"Something went wrong. Check your inputs."<<std::endl;
            EnterToContinue();
            return;
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
        return;
    case 'c':
        return;
    case 'y':
        std::cout<<"The potion invigorates you. HP healed.\n";
        play.SetHp(healvalue);
        std::cout<<"-----------------------------------"<<std::endl;
        play.PrintStats();
        EnterToContinue();
        NewState(play, realspot);
        return;
    default:
        std::cout<<"Something went wrong. Check your inputs."<<std::endl;
        EnterToContinue();
        return;
    }
}
void HealFay(Game& play, Card cc)
{
    short healvaluefay = HeartVal(cc.GetRank());
    if (cc.GetRank() == ACE)
    {
        std::cout<<"WOW! You encounter a fairy with immense aura! This ACE fairy can heal you to full hp. Press y to heal or c to Cancel...";
        AskInput();
        switch (cinput)
        {
        case 'q':
            Quit(play);
            return;
        case 'c':
            return;
        case 'y':
            std::cout<<"The fairy heals you with its magical powers. HP healed.\n";
            play.SetHp(healvaluefay);
            std::cout<<"-----------------------------------"<<std::endl;
            play.PrintStats();
            EnterToContinue();
            NewState(play, realspot);
            return;
        default:
            std::cout<<"Something went wrong. Check your inputs."<<std::endl;
            EnterToContinue();
            return;
        }
    }
    std::cout<<"You encounter a healing fairy! It can heal your hp based on the souls currently on your weapon! Press y to heal or c to Cancel... ";
    AskInput();
    switch (cinput)
    {
    case 'q':
        Quit(play);
        return;
    case 'c':
        return;
    case 'y':
        if (play.KillsExist())
        {
            std::cout<<"The fairy heals you with its magical powers. HP healed.\n";
            size_t healcalc = play.NumOfKills();
            healcalc = healcalc * healvaluefay;
            short finalheal = static_cast<short>(healcalc);
            play.SetHp(finalheal);
        }
        else
        {
            std::cout<<"You receive 0 heal and the fairy disappears."<<std::endl;
        }
        std::cout<<"-----------------------------------"<<std::endl;
        play.PrintStats();
        EnterToContinue();
        NewState(play, realspot);
        return;
    default:
        std::cout<<"Something went wrong. Check your inputs."<<std::endl;
        EnterToContinue();
        return;
    }
}
void Equip(Game& play, Card cc)
{
    std::cout<<"You found a weapon. Press y to equip the new weapon, n to skip it or c to Cancel... ";
    AskInput();
    switch (cinput)
    {
    case 'q':
        Quit(play);
        return;
    case 'c':
        return;
    case 'n':
        std::cout<<"You decide to skip the weapon and move past it."<<std::endl;
        break;
    case 'y':
        std::cout<<"You equip the new weapon."<<std::endl;
        play.ChangeWeapon(cc);
        weaponvalue = DiaVal(cc.GetRank());
        break;
    default:
        std::cout<<"Something went wrong. Check your inputs."<<std::endl;
        EnterToContinue();
        return;
    }
    std::cout<<"-----------------------------------"<<std::endl;
    play.PrintStats();
    EnterToContinue();
    NewState(play, realspot);
    return;
}
void Forge(Game& play, Card cc)
{
    short forge = DiaVal(cc.GetRank());
    if (cc.GetRank() == ACE)
    {
        std::cout<<"WOW! You encounter a forging fairy with immense aura! This ACE fairy can fully repair your weapon and remove all curses from it . Press y to accept or c to Cancel... ";
        AskInput();
        switch (cinput)
        {
        case 'q':
            Quit(play);
            return;
        case 'c':
            return;
        case 'y':
            if (!play.CheckWeapHeld())
            {
                std::cout<<"You do not have a weapon and the fairy disappears without any effect."<<std::endl;
            }
            else
            {
                play.RemoveKill(forge);
                std::cout<<"Your weapon is cleansed. The fairy disappears."<<std::endl;
            }
            break;
        default:
            std::cout<<"Something went wrong. Check your inputs."<<std::endl;
            EnterToContinue();
            return;
        }
    }
    else
    {
        std::cout<<"You encounter a forging fairy. It can remove an amount of curses from your weapon. Press y to accept or c to Cancel... ";
        AskInput();
        switch(cinput)
        {
        case 'q':
            Quit(play);
            return;
        case 'c':
            return;
        case 'y':
            if (!play.CheckWeapHeld())
            {
                std::cout<<"You do not have a weapon and the fairy disappears without any effect."<<std::endl;
            }
            else
            {
                play.RemoveKill(forge);
                std::cout<<"Your weapon is cleansed. The fairy disappears."<<std::endl;
            }
            break;
        default:
            std::cout<<"Something went wrong. Check your inputs."<<std::endl;
            EnterToContinue();
            return;
        }
    }
    std::cout<<"-----------------------------------"<<std::endl;
    play.PrintStats();
    EnterToContinue();
    NewState(play, realspot);
    return;
}
void TpAway(Game& play)
{
    if (notp==true)
    {
        std::cout<<"You can not teleport twice in a row. Enter a new room and then you can use this ability again "<<std::endl;
        EnterToContinue();
        return;
    }
    else if (notp==false && roomfull==false)
    {
        std::cout<<"You can only teleport at the start of a new room. Enter a new room and then you can use this ability again "<<std::endl;
        EnterToContinue();
        return;
    }
    else if (notp==false && roomfull==true)
    {
        std::cout<<"You want to use your teleport spell and send these cards to the end of the dungeon. Press y to continue or c to Cancel... ";
        AskInput();
        switch(cinput)
        {
        case 'q':
            Quit(play);
            return;
        case 'c':
            return;
        case 'y':
            std::cout<<"You cast your Teleport Spell and enter a new room! "<<std::endl;
            play.Teleport();
            break;
        default:
            std::cout<<"Something went wrong. Check your inputs."<<std::endl;
            EnterToContinue();
            return;
        }
    }
    std::cout<<"-----------------------------------"<<std::endl;
    play.PrintStats();
    EnterToContinue();
    return;
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

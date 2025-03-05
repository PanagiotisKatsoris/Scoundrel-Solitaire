#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include <vector>
#include <set>


class Game
{
    public:
        Game();
        virtual ~Game();
        /* method explanation

        SetHp adds a number from its argument , to the current hp variable, never exceeding 20 or dropping below 0. this represents healing or taking damage

        GetHp returns the value of current hp

        CheckWeapHelp returns boolean weapHeld variable

        ChangeWeapon replaces current weapon with one taken from argument

        PrintGameDeck prints the deck variable

        GetWeapon returns a Card type of current weapon variable

        PrintRoom prints as room consisting of four spots that a player can move to

        DealSpot deals card to a spot of the room. the spot is taken as argument

        DealRoom calls the dealspot method in each spot of room only if there are cards yet to be drawn from deck(checked by numofcards variable)

        EmptySpot empties a spot in the room by placing a null card otherwise known as Empty card in a spot which is given as argument

        EmptyRoom calls the EmptySpot function in every spot of the room

        AddKill adds value given to weapKills set. the value will be given based on the value of a monster fought

        GetLastKill returns value of lowest monster killed in weapkills set

        RemoveKill erases lowest value kill from weapon equal to the number of times given in argument

        RemoveDiamonds draws the diamond face cards along with the ace of diamonds. used to set up base game rules

        RemoveHearts draws the hearts face cards along with the ace of hearts. used to set up base game rules

        GetSpot returns the card held at given position in room[]
        */
        void SetHp(short s);//takes damage or heals hp. in case hp drops to zero or below it becomes 0, in case hp goes to 20 or above it becomes 20
        short GetHp();//returns hp var

        bool CheckWeapHeld();
        void ChangeWeapon(Card w);
        void PrintGameDeck();
        Card GetWeapon();
        void PrintRoom();
        void DealSpot(int i);
        void DealRoom();
        void EmptySpot(short sp);
        void EmptyRoom();
        void AddKill(short kill);
        short GetLastKill();
        void RemoveKill(short blsm);
        void RemoveDiamonds();
        void RemoveHearts();
        Card GetSpot(int spt);

    protected:

    private:
        /* variable explanation

        #deck is a deck of 52 cards of Deck class

        #hp represents the health points of a player and is initialized to 20 and also is manipulated through the course of the game to accept values
        between 0-20.

        #weapHeld is a boolean type variable which starts as false and once the player gets a weapon is changed to true,
        this checks if the player is barehanded or has a weapon.

        #weapon is the weapon a player holds. a player can only hold one weapon at a time and starts with null weapon.

        #room is an array that represents a room with 4 spots, each spot can either be empty represented by the null card or hold one card of the normal cards. a player can
        interact with one spot of the room at a time and room refills once three spots have "emptied".

        #numofcards counts the number of cards that have been drawn to check if the deck has been drawn

        #nullcard template null card for calling to empty spots or weapon

        #weapKills is a set of shorts which holds the values of monsters killed by a weapon. the lowest one is the first item.
        */
        Deck deck;
        unsigned short hp;
        bool weapHeld;
        Card weapon;
        Card room[4];
        short numofcards;
        Card nullcard;
        std::set<short> weapKills;
};

#endif // GAME_H

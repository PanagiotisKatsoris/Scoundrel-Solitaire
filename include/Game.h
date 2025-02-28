#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include <vector>


class Game
{
    public:
        Game();
        virtual ~Game();
        /* method explanation

        SetHp adds a number from its argument , to the current hp variable, never exceeding 20 or dropping below 0. this represents healing or taking damage

        GetHp returns the value of current hp


        */
        void SetHp(short s);//takes damage or heals hp. in case hp drops to zero or below it becomes 0, in case hp goes to 20 or above it becomes 20
        short GetHp();//returns hp var

        bool CheckWeapHeld();//returns weapHeld var
        void ChangeWeapon(Card w);//sets new weapon
        void PrintGameDeck(); //calls printdeck
        Card GetWeapon();//returns weapon
        void PrintRoom();//prints room of four cards
        void DealRoom();//deals new cards in each spot of room if that spot has the empty card. currently cards are infinitely duplicates
        void DealSpot(int i);//deals new card in a spot of room
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
        */
        Deck deck;
        unsigned short hp;
        bool weapHeld;
        Card weapon;
        Card room[4];
};

#endif // GAME_H

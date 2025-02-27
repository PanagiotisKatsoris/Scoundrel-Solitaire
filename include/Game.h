#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
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

        void SetHp(short s);//takes damage or heals hp. in case hp drops to zero or below it becomes 0, in case hp goes to 20 or above it becomes 20
        short GetHp();//returns hp var
        void SetWeapHeld(bool tf);//sets weapheld to true or false. initially it is false as game starts with empty weapon
        bool CheckWeapHeld();//returns weapHeld var
        void ChangeWeapon(Card w);//sets new weapon
        void PrintGameDeck(); //calls printdeck
        Card GetWeapon();//returns weapon
        void PrintRoom();//prints room of four cards
        void DealRoom();//deals new cards in each spot of room if that spot has the empty card. currently cards are infinitely duplicates
        void DealSpot(int i);//deals new card in a spot of room
    protected:

    private:
        Deck deck;
        unsigned short hp;//stands for health points
        bool weapHeld;
        Card weapon;
        Card room[4];
        std::vector<Card> cardsdrawn;
};

#endif // GAME_H

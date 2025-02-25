#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"


class Game
{
    public:
        Game();
        virtual ~Game();

        void SetHp(short s);
        short GetHp();
        void SetWeapHeld();
        bool CheckWeapHeld();
        void ChangeWeapon(Card w);
        void PrintGameDeck();
        Card GetWeapon();
        void PrintRoom();
    protected:

    private:
        Deck deck;
        unsigned short hp;//stands for health points
        bool weapHeld;
        Card weapon;
        Card room[4];
};

#endif // GAME_H

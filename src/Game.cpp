#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"

Game::Game()
{
    hp = 20;
    weapHeld = false;
    numofcards = 0;
}

Game::~Game()
{
    //dtor
}

void Game::PrintGameDeck()
{
    deck.PrintDeck();
}

bool Game::CheckWeapHeld()
{
    return weapHeld;
}

short Game::GetHp()
{
    return hp;
}

Card Game::GetWeapon()
{
    return weapon;
}

void Game::PrintRoom()
{
    for (int i = 0; i<4; i++)
    {
        room[i].PrintCard();
    }
}

void Game::ChangeWeapon(Card w)
{
    if(!weapHeld)
    {
        weapHeld = true;
    }
    weapon.SetRank(w.GetRank());
    weapon.SetSuit(w.GetSuit());
}

void Game::SetHp(short s)
{
    short checkhp = hp + s;
    if (checkhp < 0)
    {
        hp = 0;
    }
    else if (checkhp > 20)
    {
        hp = 20;
    }
    else
    {
        hp = checkhp;
    }
}


void Game::DealSpot(int i)
{
       switch((room[i]).GetSuit())
        {
        case 4:
            Card temp = deck.DrawCard();
            room[i]=temp;
            numofcards++;
            break;
        }
}

void Game::DealRoom()
{
    for (int i = 0; i<4; i++)
    {
        if(numofcards < 52)
        {
            DealSpot(i);
        }
    }
}

void Game::ActSpot(short sp)
{
    Card nullcard;
    room[sp] = nullcard;
}

void Game::EmptyRoom()
{
    for (short i = 0; i<4; i++)
    {
        ActSpot(i);
    }
}

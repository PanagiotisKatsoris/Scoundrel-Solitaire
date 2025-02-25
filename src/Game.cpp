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

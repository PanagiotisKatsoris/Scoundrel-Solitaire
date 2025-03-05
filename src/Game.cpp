#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include <set>

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
    std::cout<<"-----------------------------------"<<std::endl;
    for (int i = 0; i<4; i++)
    {
        room[i].PrintCard();
    }
    std::cout<<"-----------------------------------"<<std::endl;
}

void Game::ChangeWeapon(Card w)
{
    if(!weapHeld)
    {
        weapHeld = true;
    }
    weapon.SetRank(w.GetRank());
    weapon.SetSuit(w.GetSuit());
    weapKills.clear();
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
        else
        {
            break;
        }
    }
}

void Game::EmptySpot(short sp)
{
    room[sp] = nullcard;
}

void Game::EmptyRoom()
{
    for (short i = 0; i<4; i++)
    {
        EmptySpot(i);
    }
}

void Game::AddKill(short kill)
{
    weapKills.insert(kill);
}
//this returns 0 if set is empty. use this in the logic part to print a message maybe
short Game::GetLastKill()
{
    if(!weapKills.empty())
    {
        short killstemp = *weapKills.begin();
        return killstemp;
    }else
    {
        return 0;
    }
}

void Game::RemoveKill(short blsm)
{
    while(blsm >0)
    {
        weapKills.erase(weapKills.begin());
        blsm--;
    }
}

void Game::RemoveDiamonds()
{
    Card dump;
    dump = deck.DrawCard(13);
    numofcards++;
    for(int di = 23; di < 26; di++)
    {
        dump = deck.DrawCard(di);
        numofcards++;
    }
}

void Game::RemoveHearts()
{
    Card dump;
    dump = deck.DrawCard(26);
    numofcards++;
    for(int hi = 36; hi < 39; hi++)
    {
        dump = deck.DrawCard(hi);
        numofcards++;
    }
}

Card Game::GetSpot(int spt)
{
    return room[spt];
}

void Game::PrintStats()
{
    std::string tempweaponcheck = weapon.CardToString();
    std::cout<<"You have "<<GetHp()<<" health points.\nYour weapon slot is: "<<tempweaponcheck<<std::endl;
    if(weapHeld && !weapKills.empty())
    {
        int wpklltemp = *weapKills.begin();
        std::cout<<"The last monster you killed with this weapon had "<<wpklltemp<<" power."<<std::endl;
    } else if(weapHeld && weapKills.empty())
    {
        std::cout<<"You have not killed any monsters with this weapon yet."<<std::endl;
    }
}

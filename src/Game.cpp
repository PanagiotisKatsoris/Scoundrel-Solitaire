#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include <set>
#include <deque>

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
short Game::GetHp()
{
    return hp;
}
void Game::PrintStats()
{
    std::string tempweaponcheck = weapon.CardToString();
    std::cout<<"You have "<<GetHp()<<" health points.\nYour weapon slot is: "<<tempweaponcheck<<std::endl;
    if(weapHeld && !weapKills.empty())
    {
        int wpklltemp = *weapKills.begin();
        std::cout<<"Weapon cursed. Can not slay "<<wpklltemp<<"-power or higher monsters."<<std::endl;
    } else if(weapHeld && weapKills.empty())
    {
        std::cout<<"You have not slayed any monsters with this weapon yet."<<std::endl;
    }
}

bool Game::CheckWeapHeld()
{
    return weapHeld;
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
Card Game::GetWeapon()
{
    return weapon;
}
void Game::AddKill(short kill)
{
    weapKills.insert(kill);
}
short Game::GetLastKill()
{
    if(!weapKills.empty())
    {
        short killstemp = *weapKills.begin();
        return killstemp;
    }else
    {
        return 0;//this returns 0 if set is empty. use this in the logic part to print a message maybe
    }
}
void Game::RemoveKill(short blsm)
{
    while(blsm >0)
    {
        if (!weapKills.empty())
        {
            weapKills.erase(weapKills.begin());
            blsm--;
        }
        else
        {
            blsm--;
        }

    }
}
bool Game::KillsExist()
{
    return !weapKills.empty();
}
size_t Game::NumOfKills()
{
    return weapKills.size();
}

void Game::PrintGameDeck()
{
    deck.PrintDeck();
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
void Game::Teleport()
{
    for (short i = 0; i<4; i++)
    {
        secondaryDeck.push_back(GetSpot(i));
    }
    EmptyRoom();
}


void Game::PrintRoom()
{
    std::cout<<"-----------------------------------"<<std::endl;
    for (int i = 0; i<4; i++)
    {
        int spc = i+1;
        std::cout<<spc<<": ";
        room[i].PrintCard();
    }
    std::cout<<"-----------------------------------"<<std::endl;
}
void Game::DealRoom()
{
    for (int i = 0; i<4; i++)
    {
        if(numofcards < 52)
        {
            DealSpot(i);
        }
        else if (!secondaryDeck.empty())
        {
            switch((room[i]).GetSuit())
            {
            case 4:
                Card temp = secondaryDeck.front();
                room[i]=temp;
                secondaryDeck.pop_front();
                break;
            }
        }
        else
        {
            break;
        }
    }
}
void Game::EmptyRoom()
{
    for (short i = 0; i<4; i++)
    {
        EmptySpot(i);
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
void Game::EmptySpot(short sp)
{
    room[sp] = nullcard;
}
Card Game::GetSpot(int spt)
{
    return room[spt];
}

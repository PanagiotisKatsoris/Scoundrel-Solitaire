#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "CardAndDeckEnums.h"
#include <vector>
#include <set>
#include <deque>


class Game
{
    public:
        Game();
        virtual ~Game();
        /* method explanation

        SetHp adds a number from its argument , to the current hp variable, never exceeding 20 or dropping below 0. this represents healing or taking damage
        GetHp returns the value of current hp
        PrintStats prints current stats of hp weapon and if weapon exists also weapon kills(only the value of the last monster slain)

        CheckWeapHelp returns boolean weapHeld variable
        ChangeWeapon replaces current weapon with one taken from argument
        GetWeapon returns a Card type of current weapon variable
        AddKill adds value given to weapKills set. the value will be given based on the value of a monster fought
        GetLastKill returns value of lowest monster killed in weapkills set
        RemoveKill erases lowest value kill from weapon equal to the number of times given in argument
        KillsExist checks if weapKills is empty. if its not empty returns true
        NumOfKills returns the size_t of the weapKills set

        PrintGameDeck prints the deck variable
        RemoveDiamonds draws the diamond face cards along with the ace of diamonds. used to set up base game rules
        RemoveHearts draws the hearts face cards along with the ace of hearts. used to set up base game rules
        Teleport adds the four cards from room into secondaryDeck and then empties room

        PrintRoom prints as room consisting of four spots that a player can move to
        DealRoom calls the dealspot method in each spot of room only if there are cards yet to be drawn from deck(checked by numofcards variable)
        EmptyRoom calls the EmptySpot function in every spot of the room

        DealSpot deals card to a spot of the room. the spot is taken as argument
        EmptySpot empties a spot in the room by placing a null card otherwise known as Empty card in a spot which is given as argument
        GetSpot returns the card held at given position in room[]
        */
        void SetHp(short s);
        short GetHp();
        void PrintStats();

        bool CheckWeapHeld();
        void ChangeWeapon(Card w);
        Card GetWeapon();
        void AddKill(short kill);
        short GetLastKill();
        void RemoveKill(short blsm);
        bool KillsExist();
        size_t NumOfKills();

        void PrintGameDeck();
        void RemoveDiamonds();
        void RemoveHearts();
        void Teleport();

        void PrintRoom();
        void DealRoom();
        void EmptyRoom();

        void DealSpot(int i);
        void EmptySpot(short sp);
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
        #secondaryDeck is a deque which will hold the cards that are avoided through the teleport mechanic and will be dealt after initial deck is empty
        */
        Deck deck;
        unsigned short hp;
        bool weapHeld;
        Card weapon;
        Card room[4];
        short numofcards;
        Card nullcard;
        std::set<short> weapKills;
        std::deque<Card> secondaryDeck;
};

#endif // GAME_H

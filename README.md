
# Scoundrel
<p>A Solitaire Dungeon Crawl Game in the Terminal</p>
<p>This is a game based on the Scoundrel Solitaire Game Idea by Zach Gage and Kurt Bieg.
<br>It uses a basic deck of 52 cards which the player faces in a random order which represent monsters in a dungeon, healing potions, weapons etc.
<br>It follows a design commonly found in dungeon crawl games as it simulates going through a dungeon, one room at a time, and interaction with the individual cards is a simulation of fighting monsters or using items.
<br>At the time this project started there was no known way to play with this ruleset and my ultimate goal would be to port it in a game engine so people can actually play it without resorting to sub-par methods.(like this exact version which plays on the Terminal as a Text-Based Game)
</p>

## HOW TO PLAY
<p>Currently, you can try the game out by building and running it in your IDE.
<br>Otherwise you can compile it and run it directly
<br>The game accepts inputs of type **char** so only the first letter of whatever input the player might try to enter will be accepted.
<br>To do so, you simply have to type whichever character is required for your prefered action and hit Enter
</p>

## Ruleset

<p>This is simply an overview of the rules. For a more extensive description play the game. A well-refined version of the ruleset will be written here as the 1.0 release rolls out.</p>
<p>The Base mode of this game which is very similar to the original ruleset of Scoundrel according to its creators, includes a classic 52 card deck **excluding** face cards for Hearts and Diamonds as well as the Ace of Hearts and the Ace of Diamonds. The deck is shuffled and it represents the dungeon. At the start of the game 4 cards are dealt in 4 spaces which represent one room which the player is inside of. The player picks one card at a time and follows through with the appropriate action for it and then the card is discarded<br>

>Spades and Clubs represent monsters that the player fights
>
>Hearts represent potions that heal the player
>
>Diamonds represent weapons that the player equips and uses to aid them in battle with monsters
>
>>If a weapon is equipped, it stays equipped and is only discarded once a new weapon takes its place

The player starts with 20 life points (HP) and has to clear all monsters without reaching 0 HP in order to win. Monster cards deal damage equal to their power with 2 being the lowest and ACE being the highest with a value of 14. Weapons while equipped can be optionally used to tackle monsters and if so, they reduce the damage dealt by monsters according to the weapon's power.
<br>There is also a mechanic to avoid a room temporarily if the player deems they should face it at a later time.
<br>More specific rules are explained inside the game</p>

# Class Info

Here is an overview of each class inside this program
<br>Documentation of variables and methods should be as comments on the top of each class or header file

- Main
    - contains most of the functions that handle the logic of the game
- CardAndDeckEnums
    - header file that holds an enumerator for Suits and Ranks
- Card
    - creates a card which has a Suit and a Rank value and functions to set or get its variables
- Deck
    - creates a deck of cards in an orderly fashion
    - functions that draw random cards from the deck essentially return a random card from the deck but do not actually change the deck itself. Drawn cards are stored in an unordered set instead to avoid duplicates
- Game
    - variables like health of player, weapon management, deck manipulation

Have Fun
-
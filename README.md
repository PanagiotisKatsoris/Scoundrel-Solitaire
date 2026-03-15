
# Scoundrel
<p>A Solitaire Dungeon Crawl Game in the Terminal</p>
<p>This is a game based on the Scoundrel Solitaire Game Idea by Zach Gage and Kurt Bieg.
<br>It uses a standard deck of 52 cards which the player faces in a random order which represent monsters in a dungeon, healing potions, weapons etc.
<br>It follows a design commonly found in dungeon crawl games as it simulates going through a dungeon, one room at a time, and interaction with the individual cards is a simulation of fighting monsters or using items.
<br>At the time this project started there was no known way to play this game digitally and my ultimate goal would be to port it in a game engine so people can enjoy the game on their computer.
</p>

## HOW TO PLAY
<p>Download the latest release and run the executable file.
<br>It will launch Terminal in a window and you can play the game by typing commands and hitting Enter.
<br>It is text-based at the moment and so it does not have any other kind of visual elements.
</p>

## Rules

<p></p>

You start with a deck of cards which represents the **Dungeon** and **20 HP** which is your Health.
<br>The 26 **Spades** and **Clubs** represent the **monsters**.
<br>The 9 **Diamonds** from 2 to 10 represent **weapons**.
<br>Similarly the 9 **Hearts** are **potions** that heal your **HP**.
<br>Cards excluded are face cards for Hearts and Diamonds, as well as the Ace cards for Hearts and Diamonds.<br>Note that there is a choice for adding the excluded cards to the game through expansions available with explanations of their mechanics in the how-to-play section.
<br><br>
At the start of the game 4 cards are randomly drawn from the deck and are dealt in 4 spots. This represents a **room** you are in.
<br>You may choose to use the **Teleport** action which places the four cards of the room at the end of the dungeon.
<br>There is no limit to the amount of times you can use this but you can not use it twice in a row.
<br>If you do not use Teleport at the start of a room, you must face 3 of the four cards inside, one at a time.
<br>When there is only one card remaining in a room, you move into a new one and 3 new cards are dealt in the empty spots alongside the 4th card from the previous room which carries over.<br>

Picking a card from the room leads to a different action depending on the card.

* Choosing a **Weapon**
    * You may either equip it or skip it.
    * Once a weapon is equipped, it can not be discarded until a new weapon is equipped in its place.
* Choosing a **Health Potion**
    * You drink the potion and it replenishes your health according to its value.
    * A potion does not let you exceed your maximum of 20 HP and if one would cause you to do so, it simply heals you up to 20.
    * The card is then discarded.
* Choosing a **Monster**
    * You may fight the monster barehanded or with your weapon if you have one equipped.
    * Fighting using your fists deals damage to your HP according to the value of the monster. This option is always available to you, whether you have a weapon equipped or not. The card is then discarded.
    * Fighting using your equipped weapon mitigates some damage. Your weapon's value is subtracted from the monster's value and what remains is the damage that is dealt to your HP.
    * A monster that is slain using a weapon places a curse on your weapon equal to its value. Your weapon can only be used to fight monsters with a lower value in the future.
    * Curses are attached to the specific weapon and once a new one is equipped, the previous weapon alongside its cursed values are discarded.
    >Example of a fight with a weapon
    >
    >If your weapon is the 5 of Diamonds and you use it to slay the 9 of Spades, you take 4 points of damage and your 5 of Diamonds is cursed with the value of 9.
    >You may not use this weapon to slay a Jack of Clubs afterwards at any point for example.
    >Later on you use it to fight a 7 of Clubs and take 2 points of damage.
    >Your weapon is now cursed with a value of 7 and can only be used to slay 6-power or lower monsters.
    >You then equip a 7 of Diamonds.
    >Your 5 of Diamonds is discarded as well as any curses it had.
    >Your 7 of Diamonds may be used to slay any monster now and follow the same rules as stated above for any monsters it slays moving forward.
    >>Note that having a weapon equipped but choosing to fight a monsters with your fists does **NOT** place a curse on your equipped weapon.

***The game ends when your HP drops to 0 or you slay all the monsters in the dungeon.<br>Slay them all and guarantee your escape from the dungeon to win the game.***

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
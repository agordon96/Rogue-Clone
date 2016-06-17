/***********************************************************WELCOME TO ROGUE****************************************************/

HOW TO PLAY
-----------
The game is played simply; there are only five possible inputs, w, a, s, d and q. Immediately on pressing any of these keys, a
function will start. Inputting invalid keys will simply lead to a warning in the commentary section (top left of the screen)
telling you that the input is invalid.

wasd - Movement keys, moves you one to the appropriate direction
q - Quits the game
p - Uses a potion to heal 5 health

To begin the game, type bin/runMe after makefiling the entire project--but remember to type in assets/room.txt perfectly after
the bin/runMe, or the game will return you with the acknowledgement that you either didn't provide an argument or inputted
an invalid file. This text file dictates how the game works.

Once the game boots up, you will be placed as @ on the board, and your goal will be to go around collecting gold, potions,
exploring rooms and more!

SCREEN
------
There are several things you can see around the screen.

p - Potions, pick these up to gain a potion
* - Gold, pick these up to gain an additional 10 gold to your total
M - Monster, defeat it to gain 20 gold
- and | - Horizontal and vertical walls, impassable without a door
+ - Door, of which you can open to move to another room. Returning to the room will close the door
w - Weapon, of which you can collect for your endgame totals and gain one extra attack point
m - Magic spells, of which you can collect to gain another attack point
% - Stairs, blocked off from the last adventurer destroying them but can still be discovered

At the top left corner of the screen is the status message, telling you what's going on in your game when things happen.
At the bottom is your gold, potion and health count. Weapon/magic count isn't displayed until the end of the game, however your
damage dealt to a monster is shown after every swing. 0 or less health = death.

FIGHTING
--------
You start squishy, with only one damage point dealt per swing to a monster, so pick up weapons (w) and magic (m) to enhance
your abilities. You also start with 10 health and can heal injuries and even buff yourself up with potions by pressing p if
you have enough. The game will alert you if you don't have enough potions, so spam the button if you want.

To fight, move into a monster. You will swing, and so will it. Your health will go down, and so will the monster's. You cannot see 
your opponents' health counters, but yours is at the bottom. Lose all of your health and the game ends with you dying. if the
monster loses all of its health, the game will congraulate you and give you 20 extra gold. Then the monster will disappear.

ENHANCEMENTS
------------
- Usage of items, mainly weapons/magic to increase your attack power and potions to heal your health
- A fight system. Rudimentary, but it features dynamic health that gets harder as you beat more monsters and does change in
several ways based on your adventures.
- Rudimentary hallway system

LIMITATIONS
-----------
- Although the door opening sequence was intentional (moving the door a bit when opened), it resulted in the same thing 
happening for stairs and hallways even though the latter was never created.
- The assumption was made that, for the input file, the coordinates for a room began at 1, 1. This is only a limitation if 
this wasn't intended by the professor, otherwise it was merely something I did out of pure assumption.

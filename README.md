# CSC-122-Submarine-adventure
We're going to make a game about exploring the ocean in a submarine! We will be expanding this project for portfolios 2 and 3, so make sure your code is well organized and extensible.



Here's the rough outline:

The submarine starts on the surface of the ocean and descends
The submarine has a limited supply of oxygen, which depletes as it explores
The submarine can find interesting things underwater, such as treasures
The submarine eventually can return to the surface, where it will restore its oxygen before another adventure


## Motion:


The submarine can move around a grid based environment, in any of the cardinal directions. One tile of movement will occur each turn.

On the player's turn, they may type in W, A, S, or D, to move Up, Left, Down, or Right respectively.

The player can move freely through open ocean, but cannot move against a wall, or against the borders of the level. If the player makes an invalid move, you should display a message explaining why the move didn't work, and let them try again, without wasting their turn (no oxygen should be lost)

Ex)

```
 @  
    #
#####﻿
 
Enter a move: S
     
     
  @ #
#####﻿
 
 
Enter a move: S
You can't move into a wall! Try again!
Enter a move:
```

## The Level and the Camera


You should design a large level (at least 10 x 10 tiles), and use walls to make interesting features, such as the seafloor, cliffs, and coral outcroppings.

The entire level should not be visible at once. On each turn, you should display a 5x5 segment of the level that is centered around the player. If the player moves within 2 tiles of the edge of the level, the camera should not move with the player, so as to maintain the 5x5 size.

(Note that in the example, I'm representing open ocean with a blank tile.)

Ex)
```
  @  
##  #
#####
 
Enter a move: D
﻿﻿
     
     
  @  
#  ##
#####﻿
```
## The Surface and Oxygen


The player should begin the adventure at some designated spot on the surface. They will start with some amount of oxygen, and their current oxygen should be displayed every turn. Every turn will spend oxygen. If the player runs out of oxygen, they lose and the game should return to a main menu that allows them to start over. If the player ever returns to the surface (at any location), their oxygen is refilled.

Ex)
```
~~@~~
    #
   ##
 
Oxygen: 50/50
 
Enter a move: S
   
     
~~~~~
  @ #
   ##
  ###
 
Oxygen: 49/50
```
## Finding Treasure:


The player can find treasure or other interesting objects in the depths.

On the player's turn, they can opt to inspect the area around them.

If there are interesting objects adjacent to the player, information about those objects is displayed. If there is treasure, it is collected and its value is displayed.

Inspecting should not spend the player's turn.



Your game should have several different pieces of treasure, and at least a few interesting objects that don't do anything (a skeleton, a weird plant, etc)



When the player returns to the surface, the value of all pieces of treasure found on that descent are added to their total earnings, which is displayed.
Ex)
```
  ###
   ##
  @ #
  * #
#####
 
Oxygen: 32/50
 
Enter a move: inspect
 
You found a gold coin! (Value: $5)
 
Enter a move:
 
...
 
     
     
~~@~~
    #
   ##
 
You reached the surface!
Oxygen refilled.
Treasure collected:
Gold coin: +$5
Bronze Sword: +$80
Earnings this descent: +$85
 
Total Earnings: $105
 
Oxygen: 50/50
 
Enter a move:
﻿
```
## Other:


When you launch the game or die, you are shown a main menu which allows you to start the game, or quit.



Input should be validated at every step of the game! Invalid input should not spend the player's turn.



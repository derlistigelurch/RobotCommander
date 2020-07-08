# Robot Commander
A small turn based strategy game, written in C/C++.

The game is still under development. :D

It cannot be played in the current state.

## About
In this game you take control over a bunch of robots.
In order to win you have to destroy all enemy robots.

At the beginning of the game you have to choose which map should be loaded. Valid maps may only contain certain letters but more on this later.

When you start the game you will immediately notice that another terminal opens. In this new terminal you can enter your commands.
Each terminal uses pipes and message queues to communicate with the other programms.
If you now type e.g. `F` for `Fight`, three more terminals will open, one of them shows the currently loaded `map`, one shows the `log` and the last one shows the `stats` of a selected robot or terrain tile. Let's call them support windows (or terminals). 

You can close the support windows all the time, but you will lose the ability to see the log, map and/or stats and the programm will wait until you open it again.

If you close one of the support windows by accident, you have to open it manually in order to use it again.

I will add a `Makefile` later.

## Robots
Each robot consists of the same attributes.

* `Id` - random numeric value
* `Name` - name of the robot (i prefer names of old yu-gi-oh cards ;-))
* `Symbol` - char which represents your robot on the map (Default: `P` - Player, `E` - Enemy)
* `Action Points` - asd
* `Attack Radius` - asd
* `Damage` - number of d3 rolled to determine the damage
* `Description` - description of a robot
* `Health` - amount of damage a robot can take

## Map
### Valid Characters
As mentioned before, every map may only contain certain letters in order to work.

* `M` - Mountain 
* `G` - Grass
* `F` - Forest
* `B` - Building
* `W` - Water
* `S` - Spawn Point

### `.map` file
to create a valid `.map` file some rules must be followed
* the first line of every `.map` file should contain the dimensions of the map seperated by a `x`
* the second line contains the number of robots sperated by an `x`. The number of robots (`Players` + `Enemies`) should match the number of `Spawn Points`.

A valid `.map` file could look like this:
```
16x10
1x1
MMMMMMMMMMMMMMMM
MGGGFFFFGGGGGGGM
MGGFGGFFGGGGGGGM
MGGGBGBGGGGGGGGM
MSGGWWWWGGGGGGGM
MGGGBWWMWGBGGGSM
MGGGWWMMWWWGGGGM
MGGGGWWWWGBFFFFM
MGGGGGGGGFFFFFFM
MMMMMMMMMMMMMMMM
```

## Commands
### Menu Commands
* `F` - Fight
* `W` - Workshop
* `E` - Exit

### Fight Commands
* `M` - Move
* `A` - Attack
* `S` - Show
* `H` - Help
* `R` - Retreat

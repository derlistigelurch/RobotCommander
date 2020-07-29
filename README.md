# Robot Commander
A small turn based strategy game written in C/C++.

The game is still under development. :D

## About
In this game you take control over a bunch of robots.
In order to win you have to destroy all enemy robots.

At the beginning of the game you have to choose which map should be loaded. Valid maps may only contain certain letters but more on this later.

When you start the game you will immediately notice that another terminal opens. In this new terminal you can enter your commands.
Each terminal uses pipes and message queues to communicate with the other programms.
If you now type e.g. `F` for `Fight`, three more terminals will open, one of them shows the currently loaded `map`, one shows the `log` and the last one shows the `stats` of a selected robot or terrain tile. Let's call them support windows (or terminals). 

You can close the support windows all the time, but you will lose the ability to see the log, map and/or stats and the programm will wait until you open it again.

If you close one of the support windows by accident, you have to open it manually in order to use it again.

To run the game you just have to run the `RobotCommander` script in your terminal.

## Robots
Each robot consists of the same attributes.

* `Id` - random numeric value
* `Name` - name of the robot (i prefer names of old yu-gi-oh cards ;-))
* `Symbol` - char which represents your robot on the map (`P` - Player, `E` - Enemy)
* `Action Points` - Number of actions a robot can perform in one round
* `Attack Radius` - Attack range of the robot
* `Damage` - number of d3 rolled to determine the damage
* `Description` - description of a robot
* `Health` - amount of damage a robot can take

## Map
### Valid Characters
As mentioned before, every map may only contain certain letters in order to work.

* `M` - Mountain
    * Blocks attacks and movement
* `G` - Grass
* `F` - Forest
* `B` - Building
* `W` - Water
    * Moving through water costs 2 `AP`
* `S` - Spawn Point

### `.map` file
To create a valid `.map` file some rules must be followed
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

### Robots
### `.save` file
The `.save` file contains all robots. 
The first line of a new robot is the `ROBOT` tag, it indicates the beginning of a new robot. The second line contains the `ID`, the third the `SYMBOL` and so on.

A valid `ROBOT` could look like this:

```
ROBOT
ID:3
SYMBOL:P
NAME:Dark Machine-Wizard
HEALTH:12
ACTION_POINTS:2
DAMAGE:4
ATTACK_RADIUS:1
DESCRIPTION:
The ultimate robot in terms of attack and defense.
```
### `.pictures` file
At the start of the game, every robot gets a random image from the `.picture` file.
It contains some custom ASCII-art images from cartoon robots. If you want to add new images, just copy and paste them into the file. At the end of every picture has to be a new line character `'\n'`.

A valid `picture` in the `.picture` file could look like this:
```
+--------------------+
|MMMMMMMMMWMMMMMMMMMM|
|MMMNxdKKMXMMMMMMMMMM|
|MMMMMl.';dxKWXNNWWMM|
|Mk;'l..''..;,..lkoxW|
|M0loO;;c. ...;....lW|
|MMMMMWc;;..'.',d0MMM|
|MMMMMMco'Xxx..cXMMMM|
|MMMMMNl.kMMNc.XNNMMM|
|MMMMM0,OMMMMMXkXMMMM|
|MMMMM'.XMMMMMMMMMMMM|
|MMMMMckMMMMMMMMMMMMM|
|MMMMMNNMMMMMMMMMMMMM|
+--------------------+

```
 
## Commands
### Menu Commands
* `F` - Fight - start a fight
* `E` - Exit - exit game

### Fight Commands
Every parameter in a fight command is seperated by a '`:`'
* `M`|`A`|`S`|`H`|`R` - the action you want o perform
* `R` - Robot - `SYMBOL` and `ID` of a robot e.g. `E1`, `P1`, `E3`
* `N`|`E`|`S`|`W` - Direction the robot should go

#### Command parameter
* `M` - Move - move your robot in a given direction
    * M:R:N|E|S|W
* `A` - Attack - attack an enemy robot
    * A:R:R
* `S` - Show - show stats of a robot
    * S:R
* `H` - Help - displays the manual
* `R` - Retreat - reatreat from combat

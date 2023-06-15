# Bomb Flip
It's like Voltorb Flip except Voltorb is now a bomb.

- [**How to Play**](#how-to-play) 
    - [**Running**](#running)
    - [**Controls**](#controls)
- [**Building**](#building)

## How to Play
The objective of **Bomb Flip** is to flip all the tiles with values of **2** and **3**
and avoid flipping tiles with a **Bomb**.

Along the top and left side of the grid are tiles which display the **total number**
of all values in that row / column. These also display the **number of bombs**.

If a bomb value is **0**, then it is safe to **flip all tiles** in that row / column.
Tiles that have been flipped make it easier to judge whether or not to flip
other tiles.

For example, if there are **4 bombs** in a column and one of the tiles has
already been flipped, then *all* the other tiles in that column must be bombs
and so they shouldn't be flipped. These tiles can be marked to indicate
that they are bombs by pressing **L** or by using the **Marking Menu**.

The Marking Menu can also be used to indicate other values on the tiles.

### Running
The game can be played via a Switch emulator, like **Yuzu**, or on a Nintendo
Switch capable of running homebrew.

To play on Switch hardware, copy the **bombflip.nro** file onto the SD card
and launch through the system's custom firmware.

To play with an emulator, launch the emulator and then drag the **bombflip.nro**
file onto it.

### Controls

| Button | Action |
| --- | --- |
| **Left Stick**<br>or **Arrows** | Change Tile |
| **A** | Flip Tile |
| **B** | Open Marking Menu |
| **+** | Pause |
| **L** | Toggle **Bomb** Marking |
| **R** | Toggle **1** Marking |
| **ZL** | Toggle **2** Marking |
| **ZR** | Toggle **3** Marking |

## Building
To build, first make sure the code is setup in a development
environment where **libnx** is installed (this can be done with
[**devkitPro**](https://devkitpro.org/wiki/Getting_Started)).

*If not included with devkitPro, you might also need to install SDL.*

Run the **build.bat** file to compile and build the game. This
opens a console window that will automatically close when the process
completes.

If a .nro file is not produced, run **buildShowLog.bat** which does not
automatically close and will display build errors and warnings. This
will provide hints as to why the build failed.

## TODO
 - Generate puzzles
# Game of Life (Raylib)
Custom implementation of Conway's Game of Life builting using C and the Raylib graphics
library. This project features a interactive grid and simulation speed control.

## Features
- Interactive Grid: Click cells to indicate ALIVE or DEATH
- Speed Control: Can be controlled by the left and right arrow keys
- Pause: Simulation can be paused anytime to adjust the speed and interact with the grid

## Pre-requisites
- Raylib: See their [github page](https://github.com/raysan5/raylib) for installation
- GCC: For compiling, as of 3/12/2026, I am using v15.2.1

## How to Build
Simply run `make` the executable and `make clean` for removal.

## Controls
- SPACE: Toggle pause/resume
- MOUSE LEFT: Click a cell in the interactive grid while paused.
- LEFT/RIGHT Arrows: Adjust simulation speed in 0.1 intervals.
- R: Reset grid

## Rules to the Game of Life
1. **Loneliness**:A cell will die if there are fewer than two live neighbors
2. **Survival**:A cell with two or three active neighbors will live on to the next generation
3. **Overpopulation**: Any cell with more than three live neighbors will die.
4. **Reproduction** A dead cell will become a live cell if surrounded with exactly three active neighbors.

![Screencast_20260312_222029](https://github.com/user-attachments/assets/3d9f2053-6f60-4048-9602-2949ac5203f7)

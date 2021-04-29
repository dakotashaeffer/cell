# Cell, A Cellular Automata Simulator

Cell is a terminal-based [cellular automata](https://en.wikipedia.org/wiki/Cellular_automaton) simulator inspired by [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). The simulator populates a terminal window with a randomly generated grid of live and dead cells. The simulation will immediately begin, with each proceeding iteration being the result of the rule set being applied to the previous iteration. The simulation will run indefinitely until all cells in the grid die, and there is an empty grid, or if the simulation reaches a stable state where there is no change in the state of the cells from one iteration to the next. Upon ending, the simulator will report the number of cycles that passed. The simulator cannot yet account for oscillating states, so the simulation may need to be terminated with Crtl^C. The user can also define a set number of cycles to run, though the simulation may terminate early if a previously mentioned end state is reached.

## Installation

```
$ git clone https://github.com/dakotashaeffer/cell.git
$ cd cell
$ make
$ sudo make install
```

## Usage

After installation, the simulator can be run with the following command:
```
$ cell
```
This will run the default Game of Life rule set. The grid size is automatically set to a sqaure with a side length equal to the smallest dimension of the terminal window. This allows for the largest size gird to fill the terminal window while still being a square. Several parameters can be set through command line arguments. The grid size can be change, as well as the cell color. The delay time between each iteration of the simulation can be changed. The number of iterations to run can also be changed, though the program may still end before the user-defined number of iterations is reached if an end state is hit.

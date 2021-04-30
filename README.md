# Cell, A Cellular Automata Simulator

Cell is a terminal-based [cellular automata](https://en.wikipedia.org/wiki/Cellular_automaton) simulator inspired by [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). The simulator populates a terminal window with a randomly generated grid of live and dead cells. The simulation will immediately begin, with each proceeding iteration being the result of the rule set being applied to the previous iteration. The simulation will run indefinitely until all cells in the grid die and there is an empty grid, or if the simulation reaches a stable state where there is no change in the state of the cells from one iteration to the next. Upon ending, the simulator will report the number of cycles that passed. The simulator cannot yet account for oscillating states, so the simulation may need to be terminated with Crtl^C. The user can also define a set number of cycles to run, though the simulation may terminate early if a previously mentioned end state is reached.
Currently the simulator is only built for and tested on Linux systems.

## Installation

The simulator can be installed simply by run the following commands in a terminal:
```
$ git clone https://github.com/dakotashaeffer/cell.git
$ cd cell
$ make
$ sudo make install
```
The "git clone" command will download all of the files for the simulator into a file named cell. The "cd cell" command moves the current working directory into the cell file, and the "make" command compiles the simulator. The "sudo make install" command copies the cell program file to a system file so the program can be run outside of the directory it was compiled in. If the user would prefer not to install the program onto their system, the program can be run from the file it was compiled in with the "./cell" command. There is also the optional "make clean" command that will delete unneeded files from the directory the program was compiled in.

## Usage

After installation, the simulator can be run with the following command:
```
$ cell
```
This will run the default Game of Life rule set, where a live cell with 2 or 3 live neighbors stays alive, and a dead cell with 3 live neighbors comes alive. The grid size is automatically set to a sqaure with a side length equal to the smallest dimension of the terminal window. This allows for the largest size gird to fill the terminal window while still being a square. Several parameters can be set through command line arguments. The grid size can be change, as well as the cell color. The delay time between each iteration of the simulation can be changed. The number of iterations to run can also be changed, though the program may still end before the user-defined number of iterations is reached if an end state is hit. The rule set can also be modified. The number of live neighbors needed for a dead cell to come alive and the number of live neighbors needed for a live cell to stay alive can be set to any combination of numbers from 0 to 8. Use the following command to view each command line argument and their default values:
```
$ cell --help
```
The maximum grid size can be increased by decreasing the font of the terminal window the simulator is run in. 

## Example

The following command will run a simulation for 100 cycles with a cell size of 256, red colored cells, and a rule set where a dead cell will come alive if it has 3 live neighbors, and a live cell will stay alive if it has 4, 5, 6, 7, or 8 live neighbors:
```
$ cell -n 100 -s 256 -c red -b 3 -l 45678
```

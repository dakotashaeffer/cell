/* Title: main.c
 * Author: Dakota Shaeffer
 * Description: Main program for a cellular automata simulator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <argp.h>
#include <argz.h>
#include "libcell.h"

// Setup strings for version number, error reporting email, and description
const char *argp_program_version = "version 1.0";
const char *argp_program_bug_address = "shaeffer.40@osu.edu";
static char doc[] = "Simulate cellular automota.";

// Struct for arguments
struct arguments {
	double size;
	int delay;
	int color;
	int cycles;
	int survive[9];
	int born[9];
	char *argz;
	size_t argz_len;
};

// Parse arguments
static int parse_opt(int key, char *arg, struct argp_state *state) {
	struct arguments *a = (struct arguments*) state -> input;
	
	switch (key) {
		// size
		case 's': {
			if (arg != NULL) {
				a -> size = atof(arg);
			}
			break;
		}
		// delay
		case 'd': {
			if (arg != NULL) {
				a -> delay = atoi(arg);
			}
			break;
		}
		// color
		case 'c': {
			if (arg != NULL) {
				if (!strcmp(arg, "red") || !strcmp(arg, "RED")) {
					a -> color = 1;
				} else if (!strcmp(arg, "green") || !strcmp(arg, "GREEN")) {
					a -> color = 2;
				} else if (!strcmp(arg, "yellow") || !strcmp(arg, "YELLOW")) {
					a -> color = 3;
				} else if (!strcmp(arg, "blue") || !strcmp(arg, "BLUE")) {
					a -> color = 4;
				} else if (!strcmp(arg, "magenta") || !strcmp(arg, "MAGENTA")) {
					a -> color = 5;
				} else if (!strcmp(arg, "cyan") || !strcmp(arg, "CYAN")) {
					a -> color = 6;
				} else if (!strcmp(arg, "white") || !strcmp(arg, "WHITE")) {
					a -> color = 7;
				} 
			}
			break;
		}
		// number of cycles
		case 'n': {
			if (arg != NULL) {
				a -> cycles = atoi(arg);
			}
			break;
		}
		// born rule set
		case 'b': {
			if (arg != NULL) {
				char* num;
				// Check each character in rule set string, and set its corresponding
				// value in the rule set array to 1 if it is present
				for (int i = 0; i < 9; ++i) {
					num = strchr(arg, i + '0');
					if (num != NULL) {
						a -> born[i] = 1;
					} else {
						a -> born[i] = 0;
					}
				}
			}
			break;
		}
		// survives rule set
		case 'l': {
			if (arg != NULL) {
				char* num;
				for (int i = 0; i < 9; ++i) {
					num = strchr(arg, i + '0');
					if (num != NULL) {
						a -> survive[i] = 1;
					} else {
						a -> survive[i] = 0;
					}
				}
			}
			break;
		}
	}
	
	return 0;
}

// Command line flags and their descriptions
struct argp_option options[] = {
	{"size", 's', "SIZE", 0, "Number of cells in grid. [default = max terminal length to make a square]\n"},
	{"delay", 'd', "MILLISECONDS", 0, "Delay time between each iteration of the simulation. [default = 100000]\n"},
	{"color", 'c', "RED | GREEN | YELLOW | BLUE | MAGENTA | CYAN | WHITE", 0, "Color of the cells. [default = GREEN]\n"},
	{"cycles", 'n', "CYCLES", 0, "Number of cycles to run. Runs continuously if not set. [default = continuous]\n"},
	{"born", 'b', "0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8", 0, "Number of cells that must be alive around a dead cell for it to become alive [default = 3]\n"},
	{"live", 'l', "0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8", 0, "Number of cells that must be alive around a live cell for it to stay alive [default = 23]\n"},
	{0}
};

// argp struct
struct argp argp = {options, parse_opt, 0, doc, 0, 0};

int main(int argc, char **argv) {
	// initialize screen to get dimensions
	initscr();
	struct arguments arguments;
	int x;
	int y;
	
	// get window size
	getmaxyx(stdscr, y, x);
	
	// set grid size to square of smaller dimension minus two to all for printing of end message
	if (y > x) {
		arguments.size = (x - 2) * (x - 2);
	} else {
		arguments.size = (y - 2) * (y - 2);
	}
	
	// set default argument values
	arguments.delay = 100000;
	arguments.cycles = -1;
	arguments.color = 2;
	memset(arguments.survive, 0, sizeof arguments.survive);
	memset(arguments.born, 0, sizeof arguments.survive);
	arguments.survive[2] = 1;
	arguments.survive[3] = 1;
	arguments.born[3] = 1;
	
	// close window here to prevent issues if user only passes help or usage arguments
	endwin();
	
	// parse arguments
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	// square root of grid size
	int sq = (int) sqrt(arguments.size);
	
	// grids 1 and 2 to cycle between, and empty grid for end state checking
	int grid1[sq][sq];
	int grid2[sq][sq];
	int emptyGrid[sq][sq];
	
	// initialize grid2 and empty grid to 0
	memset(emptyGrid, 0, sizeof emptyGrid);
	memset(grid2, 0, sizeof grid2);
	
	// number of cycles the simulation goes through
	int cycles = 0;
	
	// pointers to grids
	int* gridPtr = &grid1[0][0];
	int* newGridPtr = &grid2[0][0];
	int* tmpPtr;
	
	// random seed for srand
	time_t t;							
	srand((unsigned) time(&t));	
	
	// initialize window and set color values to max intensities
	initscr();
	refresh();
	start_color();
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_YELLOW, 1000, 1000, 0);
	init_color(COLOR_BLUE, 0, 0, 1000);
	init_color(COLOR_MAGENTA, 1000, 0, 1000);
	init_color(COLOR_CYAN, 0, 1000, 1000);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_pair(1, arguments.color, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	
	// initialize grid1 to random values
	initializeGrid(gridPtr, sq);
	
	// print initial grid
	printGrid(gridPtr, sq);
	
	// run simulation
	if (arguments.cycles == -1) {
		// run simulation for undertermined number of cycles if user did not specify number of cycles
		// end simulation if the state of each grid is stable, meaning there is no change, or if every cell died 
		// and the grid is empty
		while (memcmp(grid1, grid2, sizeof grid1) != 0 && memcmp(emptyGrid, grid1, sizeof emptyGrid) != 0) {
			// wait before changing grid so user can see changes
			delay(arguments.delay);
			
			// determine next state based on current state
			updateGrid(gridPtr, newGridPtr, sq, arguments.survive, arguments.born);
			
			// print new state
			printGrid(newGridPtr, sq);
			
			// swap pointers for grids
			tmpPtr = gridPtr;
			gridPtr = newGridPtr;
			newGridPtr = tmpPtr;
			
			// increment cycle count
			++cycles;
		}
	} else {
		// run simulation for a user defined number of cycles, ending early if end states are met
		for (int i = 0; i < arguments.cycles; ++i) {
			if (memcmp(grid1, grid2, sizeof grid1) == 0 || memcmp(grid1, emptyGrid, sizeof emptyGrid) == 0) {
				break;
			} else {
				delay(arguments.delay);
				updateGrid(gridPtr, newGridPtr, sq, arguments.survive, arguments.born);
				printGrid(newGridPtr, sq);
				tmpPtr = gridPtr;
				gridPtr = newGridPtr;
				newGridPtr = tmpPtr;
				++cycles;
			}
		}
	}
	
	// tell user simulation ended after number of cycles
	printw("\nSimulation ended after %d cycles. Press any key to close...", cycles);
	
	// wait for user to press any key
	getch();
	
	// close window
	endwin();
	
	return 0;
}

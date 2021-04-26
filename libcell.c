/* Title: libcell.c
 * Author: Dakota Shaeffer
 * Description: Header file with cellular automata functions.
 */

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "libcell.h"

// set each cell of grid randomly to 1 or 0
void initializeGrid(int *grid, int sq) {
	for (int i = 0; i < sq; ++i) {
		for (int j = 0; j < sq; ++j) {
			*(grid + (i * sq) + j) = rand() % 2;
		}
	}
}

// print the current state of the grid to the terminal window
void printGrid(int *grid, int sq) {	
	// clear and refresh window
	clear();
	refresh();
	
	// check each cell to see if it is alive (1) or dead (0)
	// print 'o' for live cells, and spaces for dead cells
	// extra spaces are for formatting purposes
	for (int i = 0; i < sq; ++i) {
		for (int j = 0; j < sq; ++j) {
			if (*(grid + (i * sq) + j) == 1) {					
				printw(" o");
			} else {
				printw("  ");
			}
		}
		printw("\n");
	}
	
	refresh();	
}

// wait for a specified amount of time
void delay(int milliseconds) {
	clock_t startTime = clock();					

	while(clock() < startTime + milliseconds) 			
		;
}

// evaluate each cell based on its location in the grid and the states of its neighbors
// each special case for a cells position in the grid allows for the grid to wrap around on itself
void updateGrid(int *oldGrid, int *newGrid, int sq, int survive[], int born[]) {
	 // number of live neighbors
	 int sum;
	
	 for (int i = 0; i < sq; ++i) {
		for (int j = 0; j < sq; ++j) {
			// top row
			if (i == 0) {
				// top left corner
				if (j == 0) {
					sum = *(oldGrid + ((sq - 1) * sq) + (sq - 1)) + 
						  *(oldGrid + ((sq - 1) * sq) + j) +
						  *(oldGrid + ((sq - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (sq - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + ((i + 1) * sq) + (sq - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq) + (j + 1));
					// set value of current cell in new grid to 1 or 0 based on alive neighbors and rule set
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				}
				// top right corner
				else if (j == sq - 1) {
					sum = *(oldGrid + ((sq - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((sq - 1) * sq) + j) +
						  *(oldGrid + ((sq - 1) * sq)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq)) +
						  *(oldGrid + ((i + 1) * sq) + (j - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq));
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				} 
				// all other cells in top row
				else {
					sum = *(oldGrid + ((sq - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((sq - 1) * sq) + j) +
						  *(oldGrid + ((sq - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + ((i + 1) * sq) + (j - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq) + (j + 1));
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				}
			}
			// bottom row
			else if (i == sq - 1) {
				// bottom left corner
				if (j == 0) {
					sum = *(oldGrid + ((i - 1) * sq) + (sq - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (sq - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + sq - 1) +
						  *(oldGrid + j) +
						  *(oldGrid + j + 1);
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				} 
				// bottom right corner
				else if (j == sq - 1) {
					sum = *(oldGrid + ((i - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq)) +
						  *(oldGrid + j - 1) +
						  *(oldGrid + j) +
						  *(oldGrid);
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				} 
				// all other cells in bottom row
				else {
					sum = *(oldGrid + ((i - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + j - 1) +
						  *(oldGrid + j) +
						  *(oldGrid + j + 1);
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				}
			} 
			// all other rows of cells
			else {
				// left column
				if (j == 0) {
					sum = *(oldGrid + ((i - 1) * sq) + (sq - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (sq - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + ((i + 1) * sq) + (sq - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq) + (j + 1));
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				} 
				// right column
				else if (j == sq - 1) {
					sum = *(oldGrid + ((i - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq)) +
						  *(oldGrid + ((i + 1) * sq) + (j - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq));
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				} 
				// all other cells
				else {
					sum = *(oldGrid + ((i - 1) * sq) + (j - 1)) + 
						  *(oldGrid + ((i - 1) * sq) + j) +
						  *(oldGrid + ((i - 1) * sq) + (j + 1)) +
						  *(oldGrid + (i * sq) + (j - 1)) +
						  *(oldGrid + (i * sq) + (j + 1)) +
						  *(oldGrid + ((i + 1) * sq) + (j - 1)) +
						  *(oldGrid + ((i + 1) * sq) + j) +
						  *(oldGrid + ((i + 1) * sq) + (j + 1));
					*(newGrid + (i * sq) + j) = evaluateCell((*(oldGrid + (i * sq) + j)), sum, survive, born);
				}
			}
		}
	 }
}

// evaluate each cell based on its value, its alive neighbors, and the rule set
int evaluateCell(int cell, int sum, int survive[], int born[]) {
	// live cell
	if (cell == 1) {
		// cell stays alive if the number of its alive neighbors matches any of the values in the rule set
		for (int i = 0; i < 9; ++i) {
			if (survive[i] == 1 && sum == i) {
				return 1;
			}
		}
		// otherwise the cell dies
		return 0;
	} 
	// dead cell
	else {
		// cell comes alive if the number of its alive neighbors matches any of the values in the rule set
		for (int i = 0; i < 9; ++i) {
			if (born[i] == 1 && sum == i) {
				return 1;
			}
		}
		// otherwise cell stays dead
		return 0;
	}
}
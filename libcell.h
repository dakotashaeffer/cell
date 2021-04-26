void initializeGrid(int *grid, int sq);

void printGrid(int *grid, int sq);

void delay(int milliseconds);
	
void updateGrid(int *oldGrid, int *newGrid, int sq, int survive[], int born[]);
	
int evaluateCell(int cell, int sum, int survive[], int born[]);

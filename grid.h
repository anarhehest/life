#ifndef GRID_H
#define GRID_H

#define CELL_SIZE 10
#define GRID_WIDTH 80
#define GRID_HEIGHT 60

void updateGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
void renderGrid(SDL_Renderer* renderer, int grid[GRID_HEIGHT][GRID_WIDTH]);

#endif // GRID_H

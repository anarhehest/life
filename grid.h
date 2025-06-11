#ifndef GRID_H
#define GRID_H

#define CELL_SIZE 11

int GRID_WIDTH, GRID_HEIGHT;

void updateGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
void renderGrid(SDL_Renderer* renderer, int grid[GRID_HEIGHT][GRID_WIDTH]);

#endif // GRID_H

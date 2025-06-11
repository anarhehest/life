#include <SDL.h>
#include "grid.h"

void updateGrid(int grid[GRID_HEIGHT][GRID_WIDTH]) {
    int tmpGrid[GRID_HEIGHT][GRID_WIDTH] = {0};

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            int aliveNeighbors = 0;

            // Count alive neighbors
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    int newY = y + dy;
                    int newX = x + dx;
                    if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                        aliveNeighbors += grid[newY][newX];
                    }
                }
            }

            // Apply Game of Life rules
            if (grid[y][x] == 1) {
                tmpGrid[y][x] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0; // Cell survives
            } else {
                tmpGrid[y][x] = (aliveNeighbors == 3) ? 1 : 0; // Cell becomes alive
            }
        }
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = tmpGrid[y][x];
        }
    }
}

void renderGrid(SDL_Renderer* renderer, int grid[GRID_HEIGHT][GRID_WIDTH]) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_Rect cell = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            SDL_RenderFillRect(renderer, &cell);


            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

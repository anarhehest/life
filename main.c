#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "grid.h"

#define DELAY 250

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = {64, 64, 64};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("./resources/Roboto-Medium.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game Of Life",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int grid[GRID_HEIGHT][GRID_WIDTH] = {0};
    int running = 1;
    int paused = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x / CELL_SIZE;
                int y = event.button.y / CELL_SIZE;

                if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
                    grid[y][x] = !grid[y][x];
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    paused = !paused;
                    printf("Game %s\n", paused ? "paused" : "unpaused");
                }
            }
        }

        if (!paused)
            updateGrid(grid);

        renderGrid(renderer, grid);

        const char* stateText = paused ? "Game is PAUSED" : "Game is RUNNING";
        renderText(renderer, font, stateText, 10, 10);
        renderText(renderer, font, "Press SPACE to pause/unpause", 10, 40);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

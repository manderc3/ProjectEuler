/* Graph rendering!
   Well, very specific tree rendering for very specific use cases. 
   I.e. visualing my solution for project euler's eighteenth problem.
   Written in C++ using SDL
   Yay!
   By Chris Mander (@manderc3) */

/* Doesn't have all the SDL null checking boilerplate. Living dangerously today. :) */
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <stack>
#include <thread>
#include <vector>

#include "common.h"

static constexpr unsigned SCREEN_WIDTH  = 600;
static constexpr unsigned SCREEN_HEIGHT = 480;

static SDL_Window* window;
static SDL_Surface* screen_surface;

static bool is_initialised = false;

void graph_render(const std::vector<std::shared_ptr<Node>>& current_path,
		  const std::vector<std::shared_ptr<Node>>& blocked_nodes)
{
  if (is_initialised) {

    auto root = current_path.front();
    
    SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format,
						     0xFF, 0xFF, 0xFF));
    
    SDL_UpdateWindowSurface(window);

  }
}

void graph_init()
{
  if (!is_initialised) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Animated Graph Yay!",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      SCREEN_WIDTH,
			      SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);

    screen_surface = SDL_GetWindowSurface(window);

    is_initialised = true;
  }
}

/* Graph rendering!
   Well, very specific tree rendering for very specific use cases. 
   I.e. visualing my solution for project euler's eighteenth problem.
   Written in C++ using SDL
   Yay!
   By Chris Mander (@manderc3) */

/* Doesn't have all the SDL null checking boilerplate. Living dangerously today. :) */
#include <SDL2/SDL.h>
#include <chrono>
#include <stack>
#include <thread>
#include <vector>

#include "common.h"

static constexpr unsigned SCREEN_WIDTH  = 600;
static constexpr unsigned SCREEN_HEIGHT = 480;

static SDL_Window* window;
static SDL_Surface* screen_surface;


static void graph_run()
{
  SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format,
						     0xFF, 0xFF, 0xFF));

    
  SDL_UpdateWindowSurface(window);

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void graph_init()
{
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Animated Graph Yay!",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH,
			    SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);

  screen_surface = SDL_GetWindowSurface(window);

  std::thread t(graph_run);

  t.join();
}

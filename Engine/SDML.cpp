//-----------------------------------------------------------------------------
// SDML.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDML.h"

//-----------------------------------------------------------------------------
SDML::SDML()
{
  type_ = SYS_SDL;
}

//-----------------------------------------------------------------------------
SDML::~SDML()
{
}

//-----------------------------------------------------------------------------
int SDML::init()
{
  //Initialize the SDL subsystems
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "SDL could not be initialized: " << SDL_GetError << std::endl;
    return -1;
  }

  //Initialize PNG support through SDL2_image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    std::cout << "SDL_image could not be initialized: " << IMG_GetError << std::endl;
    return -1;
  }

  //Initialize SDL_ttf
  if (TTF_Init() == -1)
  {
    std::cout << "SDL_ttf could not be initialized: " << TTF_GetError << std::endl;
    return -1;
  }

  std::cout << "[SDML]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void SDML::shutdown()
{
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

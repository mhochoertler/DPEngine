//-----------------------------------------------------------------------------
// Renderer.cpp
//-----------------------------------------------------------------------------
#include <iostream>

#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
Renderer::Renderer()
{
  type_ = SYS_RENDERER;
}

//-----------------------------------------------------------------------------
int Renderer::init()
{
  //Sets the resolution appropriate to the clients display
  setDisplayMode();
  
  int height = current_display_.h;
  int width = current_display_.w;

  const char* title = "Game";
  
  //Initialize main window
  window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_MAXIMIZED);

  if (window_ == NULL)
  {
    std::cout << "Window could not be created!" << SDL_GetError() << std::endl;
    return -1;
  }
    
  //Initialize renderer
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

  if (renderer_ == NULL)
  {
    std::cout << "Renderer could not be created!" << SDL_GetError() << std::endl;
    return - 1;
  }

  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  std::cout << "[Renderer]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void Renderer::shutdown()
{
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
}

//-----------------------------------------------------------------------------
Renderer::~Renderer()
{
}

//-----------------------------------------------------------------------------
bool Renderer::setDisplayMode()
{
  //for now, just one display is supported
  int display_index = 0;

  //Get current display mode of one display
  std::cout << "Receiving client display information... " << std::endl;
  if (SDL_GetCurrentDisplayMode(display_index, &current_display_) != 0)
  {
    //In case of error...
    SDL_Log("Could not get display mode for video display #%d: %s",
            display_index, SDL_GetError());
    return false;
  }
  else
  {
    //On success, print the current display mode.
    SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.",
      display_index, current_display_.w, current_display_.h, current_display_.refresh_rate);
    std::cout << std::endl;
  }

  return true;
}

//-----------------------------------------------------------------------------
void Renderer::renderScene(const Scene &scene)
{
  Camera* camera = scene.getTargetCamera();

  //Clears the screen
  SDL_RenderClear(renderer_);

  scene.draw(this);

  //Renders the scene on the screen
  SDL_RenderPresent(renderer_);
}

//-----------------------------------------------------------------------------
SDL_Window* Renderer::getWindow()
{
  return window_;
}

//-----------------------------------------------------------------------------
SDL_Renderer* Renderer::getRenderer()
{
  return renderer_;
}

//-----------------------------------------------------------------------------
SDL_DisplayMode* Renderer::getDisplayMode()
{
  return &current_display_;
}
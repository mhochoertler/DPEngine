//-----------------------------------------------------------------------------
// Renderer.h
// Class holding variables used for rendering the game
//-----------------------------------------------------------------------------
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "System.h"

class Scene;

class Renderer : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Private Constructor
    //
    Renderer();

    //-------------------------------------------------------------------------
    // Main game window
    //
    SDL_Window* window_;

    //-------------------------------------------------------------------------
    // SDL_Renderer used for rendering to the window
    //
    SDL_Renderer* renderer_;

    //-------------------------------------------------------------------------
    // Holds information about the clients display
    //
    SDL_DisplayMode current_display_;

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Renderer();

    //-------------------------------------------------------------------------
    // Sets the current display mode to the resolution of the clients display
    //
    bool setDisplayMode();

    void renderScene(const Scene &scene);

    //-------------------------------------------------------------------------
    // Getter Methods
    //
    SDL_Window* getWindow();

    SDL_Renderer* getRenderer();

    SDL_DisplayMode* getDisplayMode();

    //-------------------------------------------------------------------------
    // Initializes the window and renderer. If no parameters are passed, the
    // window is sized to the clients display resolution.
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down
    //
    void shutdown();
};
#endif // !RENDERER_H


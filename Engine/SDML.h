//-----------------------------------------------------------------------------
// SDML.h
// A wrapper for SDL2-2.0.7, SDL2_ttf-2.0.14 & SDL2_image-2.0.1
// Used to initialize the SDL_Subsystems
//-----------------------------------------------------------------------------
#ifndef SDML_H
#define SDML_H

#include "System.h"

class SDML : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    SDML();

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~SDML();

    //-------------------------------------------------------------------------
    // Initializes the used SDL_Subsystems
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the SDL_Subsystems down
    //
    void shutdown();
};
#endif // !SDML_H
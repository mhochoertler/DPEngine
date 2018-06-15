//-----------------------------------------------------------------------------
// Engine.h
// Initializes the subsystems and processes an AbstractGame
//-----------------------------------------------------------------------------
#ifndef ENGINE_H
#define ENGINE_H

#include "AbstractGame.h"

class Engine
{
  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    Engine();

    //-------------------------------------------------------------------------
    // Used for singleton implementation
    //
    static Engine* instance_;

    //-------------------------------------------------------------------------
    // Starts all necessary subsystems
    //
    bool startSubsystems();

    //-------------------------------------------------------------------------
    // Stops all running subsystems
    //
    void stopSubsystems();

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Engine();

    //-------------------------------------------------------------------------
    // Returns a static instance
    //
    static Engine* instance();

    //-------------------------------------------------------------------------
    // Starts the main gameloop
    //
    bool runGame(AbstractGame* game);

    //-------------------------------------------------------------------------
    // Stops the main gameloop
    //
    bool stopGame();
};
#endif // !ENGINE_H

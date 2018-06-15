//-----------------------------------------------------------------------------
// AbstractGame.h
// Game structur used by the engine
//-----------------------------------------------------------------------------
#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <map>

#include "Scene.h"

class IDrawable;

class AbstractGame
{
  friend class GameManager;

  private:
    //-------------------------------------------------------------------------
    // The scene which gets rendered
    //
    Scene* current_scene_;

    //-------------------------------------------------------------------------
    // Map of all scenes
    //
    std::map<std::string, Scene*> scenes_;

    //-------------------------------------------------------------------------
    // Returns the current scene
    //
    Scene* getCurrentScene();

  public:
    //-------------------------------------------------------------------------
    // Constructor
    //
    AbstractGame();

    //-------------------------------------------------------------------------
    // Destructor
    //
    virtual ~AbstractGame();

    //-------------------------------------------------------------------------
    // Use this for initializing your game. It's called before your game starts.
    //
    virtual void init() = 0;

    //-------------------------------------------------------------------------
    // Creates a new scene
    //
    Scene* createNewScene(std::string scene_name);

    //-------------------------------------------------------------------------
    // Changes the scene to render
    //
    void changeScene(std::string scene_name);

    //-------------------------------------------------------------------------
    // Returns the scene described by the string
    //
    Scene* getScene(std::string scene_name);
};
#endif // !ABSTRACTGAME_H

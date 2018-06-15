//-----------------------------------------------------------------------------
// AbstractGame.h
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>

#include "AbstractGame.h"
#include "IDrawable.h"

//-----------------------------------------------------------------------------
AbstractGame::AbstractGame() : current_scene_(NULL)
{
}

//-----------------------------------------------------------------------------
AbstractGame::~AbstractGame()
{
}

//-----------------------------------------------------------------------------
Scene* AbstractGame::createNewScene(std::string scene_name)
{
  if(scenes_.find(scene_name) != scenes_.end())
  {
    std::cout << "Scenename already taken! - " << scene_name << std::endl;
    return NULL;
  }
  else
  {
    scenes_[scene_name] = new Scene();

    if (current_scene_ == NULL) current_scene_ = scenes_[scene_name];
    return scenes_[scene_name];
  }
}

//-----------------------------------------------------------------------------
void AbstractGame::changeScene(std::string scene_name)
{
  if(scenes_.find(scene_name) != scenes_.end())
  { 
    current_scene_ = scenes_[scene_name];
  }
}

//-----------------------------------------------------------------------------
Scene* AbstractGame::getScene(std::string scene_name)
{
  if (scenes_.find(scene_name) == scenes_.end())
  {
    std::cout << "Scene " + scene_name + " doesn't exist!" << std::endl;
    return NULL;
  }

  return scenes_[scene_name];
}

//-----------------------------------------------------------------------------
Scene* AbstractGame::getCurrentScene()
{
  return current_scene_;
}



//-----------------------------------------------------------------------------
// GameManager.cpp
//-----------------------------------------------------------------------------
#include "GameManager.h"
#include "AbstractGame.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "CollisionDetector.h"
#include "SystemManager.h"
#include "Scene.h"

GameManager* GameManager::instance_ = 0;

//-----------------------------------------------------------------------------
GameManager::GameManager() : is_running_(true)
{

}

//-----------------------------------------------------------------------------
GameManager::~GameManager()
{
  
}

//-----------------------------------------------------------------------------
GameManager* GameManager::instance()
{
  if(instance_ == 0)
  {
    instance_ = new GameManager();
  }
  return instance_;
}

//-----------------------------------------------------------------------------
void GameManager::startGameloop(AbstractGame* game)
{
  game->init();

  Scene* cur_scene = NULL;

  while(is_running_)
  {
    handleInput();

    cur_scene = game->getCurrentScene();

    if(cur_scene != NULL)
    {
      cur_scene->update();
      SystemManager::instance()->getSubSystem<Renderer>()->renderScene(*cur_scene);
    }
  }
}

//-----------------------------------------------------------------------------
void GameManager::handleInput()
{
  InputHandler* input_sys = SystemManager::instance()->getSubSystem<InputHandler>();

  input_sys->checkForInput();

  if(input_sys->getKey(WINDOW_QUIT)) stopGameloop();
}

//-----------------------------------------------------------------------------
void GameManager::stopGameloop()
{
  is_running_ = false;
}
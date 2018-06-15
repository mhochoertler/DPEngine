//-----------------------------------------------------------------------------
// Engine.cpp
//-----------------------------------------------------------------------------
#include "Engine.h"
#include "GameManager.h"
#include "SystemManager.h"

Engine* Engine::instance_ = 0;

//-----------------------------------------------------------------------------
Engine::Engine()
{
}

//-----------------------------------------------------------------------------
Engine::~Engine()
{
}

//-----------------------------------------------------------------------------
Engine* Engine::instance()
{
  if(instance_ == 0)
  {
    instance_ = new Engine();
  }

  return instance_;
}

//-----------------------------------------------------------------------------
bool Engine::startSubsystems()
{
  for(int sys_type = SYS_SDL; sys_type < SYS_MAX; sys_type++)
  {
    if(SystemManager::instance()->createSubSystem(static_cast<SystemType>(sys_type)) != 0)
    {
      return false;
    }
  }

  return true;
}

//-----------------------------------------------------------------------------
void Engine::stopSubsystems()
{
  for(int sys_type = SYS_MAX; sys_type >= SYS_SDL; sys_type--)
  {
    SystemManager::instance()->deleteSubSystem(static_cast<SystemType>(sys_type));
  }
}

//-----------------------------------------------------------------------------
bool Engine::runGame(AbstractGame* game)
{
  if(!startSubsystems())
  {
    stopSubsystems();
    return false;
  }

  GameManager::instance()->startGameloop(game);

  stopSubsystems();

  return true;
}

//-----------------------------------------------------------------------------
bool Engine::stopGame()
{
  GameManager::instance()->stopGameloop();
  return true;
}
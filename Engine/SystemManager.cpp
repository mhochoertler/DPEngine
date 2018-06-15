//-----------------------------------------------------------------------------
// SystemManager.cpp
//-----------------------------------------------------------------------------
#include <iostream>

#include "SystemManager.h"
#include "SDML.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "CollisionResolver.h"
#include "CollisionDetector.h"
#include "TextureLoader.h"
#include "MainTimer.h"

SystemManager* SystemManager::instance_ = 0;

//-----------------------------------------------------------------------------
SystemManager::SystemManager()
{
}

//-----------------------------------------------------------------------------
SystemManager::~SystemManager()
{
}

//-----------------------------------------------------------------------------
SystemManager* SystemManager::instance()
{
  if(instance_ == 0)
  {
    instance_ = new SystemManager();
  }

  return instance_;
}

//-----------------------------------------------------------------------------
int SystemManager::createSubSystem(SystemType type)
{
  System* system = 0;

  switch(type)
  {
    case SYS_SDL: 
      system = new SDML();
      break;
    case SYS_RENDERER: 
      system = new Renderer();
      break;
    case SYS_INPUT: 
      system = new InputHandler();
      break;
    case SYS_CRESOLVER: 
      system = new CollisionResolver();
      break;
    case SYS_CDETECTOR:
      system = new CollisionDetector();
      break;
    case SYS_TEXLOADER: 
      system = new TextureLoader();
      break;
    case SYS_TIMER: 
      system = new MainTimer();
      break;
    default:
      std::cout << "Couldn't create Subsystem, unknown Systemtype: " << type << std::endl;
  }

  if(system->init() == 0)
  {
    sub_systems_[type] = system;
    return 0;
  }
  else return - 1;
}

//-----------------------------------------------------------------------------
void SystemManager::deleteSubSystem(SystemType type)
{
  if(sub_systems_.find(type) != sub_systems_.end())
  {
    sub_systems_[type]->shutdown();

    delete sub_systems_[type];
    sub_systems_.erase(type);
  }
}
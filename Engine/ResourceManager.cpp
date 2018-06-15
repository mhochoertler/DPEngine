//-----------------------------------------------------------------------------
// ResourceManager.h
//-----------------------------------------------------------------------------
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = 0;

//-----------------------------------------------------------------------------
ResourceManager::ResourceManager()
{

}

//-----------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{

}

//-----------------------------------------------------------------------------
ResourceManager* ResourceManager::instance()
{
  if(instance_ == 0)
  {
    instance_ = new ResourceManager();
  }

  return instance_;
}


//-----------------------------------------------------------------------------
// Scene.cpp
//-----------------------------------------------------------------------------
#include <cmath>
#include <SDL.h>
#include <iomanip>
#include <sstream>

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "SystemManager.h"
#include "Texture.h"
#include "IDrawable.h"

//-----------------------------------------------------------------------------
Scene::Scene() : object_count_(0)
{
  Renderer* renderer = SystemManager::instance()->getSubSystem<Renderer>();

  int width = renderer->getDisplayMode()->w;
  int height = renderer->getDisplayMode()->h;

  target_camera_ = new Camera(width, height);
}

//-----------------------------------------------------------------------------
Scene::~Scene()
{
  delete target_camera_;
}

//-----------------------------------------------------------------------------
void Scene::draw(Renderer* system) const
{
  if(target_camera_ != NULL)
  {
    for (auto object : objects_)
    {
      if(isInView(object.second)) object.second->draw(system, target_camera_);
    }
  }
}

//-----------------------------------------------------------------------------
bool Scene::isInView(IDrawable* object) const
{
  if (object->sprite_ == NULL) return false;

  SDL_Rect obj_rect = { 
    object->origin_.x - object->sprite_->width_ / 2,
    object->origin_.y - object->sprite_->height_ / 2,
    object->sprite_->width_, object->sprite_->height_ 
  };

  SDL_Rect camera_rect = { 
    target_camera_->origin_.x - target_camera_->width_ / 2, 
    target_camera_->origin_.y - target_camera_->height_ / 2,
    target_camera_->width_, target_camera_->height_ 
  };

  return static_cast<bool>(SDL_HasIntersection(&obj_rect, &camera_rect));
}

//-----------------------------------------------------------------------------
void Scene::update()
{
  for (auto object : objects_)
  {
    object.second->update();
  }
}

//-----------------------------------------------------------------------------
Camera* Scene::getTargetCamera() const
{
  return target_camera_;
}

//-----------------------------------------------------------------------------
int Scene::getObjectCount() const
{
  return object_count_;
}

//-----------------------------------------------------------------------------
void Scene::addObject(IDrawable &object, int x, int y)
{
  object.scene_ = this;
  object.setOrigin(Vector2D(x, y));

  if (object.getObjectName().empty())
  {
    std::stringstream name;
    name << "Object" << std::setfill('0') << std::setw(3) << getObjectCount();
    object.rename(name.str());
  }

  object.start();
  objects_[object.getObjectName()] = &object;

  object_count_++;
}
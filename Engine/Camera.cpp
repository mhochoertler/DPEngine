//-----------------------------------------------------------------------------
// Graphics.cpp
//-----------------------------------------------------------------------------
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"
#include "IDrawable.h"

//-----------------------------------------------------------------------------
Camera::Camera(int width, int height) : width_(width), height_(height), 
                                        origin_(0, 0), obj_to_follow_(NULL)
{
}

//-----------------------------------------------------------------------------
Camera::~Camera()
{
}

//-----------------------------------------------------------------------------
Vector2D Camera::getOrigin() const
{
  return origin_;
}

void Camera::followObject(IDrawable* object)
{
  obj_to_follow_ = object;
}

void Camera::update()
{
  if(obj_to_follow_) origin_ = obj_to_follow_->getOrigin();
}
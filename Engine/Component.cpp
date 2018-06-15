#include "Component.h"
#include "IDrawable.h"

Component::Component(IDrawable* object) : parent_object_(object)
{
}

Component::Component()
{
}

Component::~Component()
{

}

ComponentType Component::getType() const
{
  return type_;
}
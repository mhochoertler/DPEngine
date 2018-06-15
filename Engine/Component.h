#ifndef COMPONENT_H
#define COMPONENT_H

#include "ComponentType.h"

class IDrawable;

class Component
{
  protected:
    ComponentType type_;

    IDrawable* parent_object_;

  public:
    Component();
    Component(IDrawable* object);
    virtual ~Component() = 0;

    ComponentType getType() const;
};
#endif // !COMPONENT_H

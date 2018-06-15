//-----------------------------------------------------------------------------
// CollisionResolver.cpp
// Used for resolving collisons between objects in the scene
//-----------------------------------------------------------------------------
#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H

#include "System.h"
#include "Vector2D.h"

struct SDL_Rect;
class IDrawable;

//-------------------------------------------------------------------------
// Struct keeping all information about the collision
//
typedef struct _COLLISION_INFO_
{
  bool collisionTop = false;
  bool collisionBtm = false;
  bool collisionRight = false;
  bool collisionLeft = false;
}CollisionInfo;

class CollisionResolver : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    CollisionResolver();

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~CollisionResolver();

    //-------------------------------------------------------------------------
    // Simple recalculation of the given position, so no collision happens with
    // the given rect
    //
    void resolveCollision(IDrawable &self, IDrawable &colliding_object);

    //-------------------------------------------------------------------------
    // Initializies the system
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down
    //
    void shutdown();
};
#endif // !COLLISIONRESOLVER_H

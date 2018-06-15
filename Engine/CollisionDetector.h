//-----------------------------------------------------------------------------
// CollisionDetector.h
// Used for detecting collisions in the scene
//-----------------------------------------------------------------------------
#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "System.h"

class Scene;
class IDrawable;

typedef struct _CONTACTINFO_
{
  bool top_ = false;
  bool btm_ = false;
  bool right_ = false;
  bool left_ = false;
}ContactInfo;

class CollisionDetector : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    CollisionDetector();

    ContactInfo* contact_info_;

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~CollisionDetector();

    //-------------------------------------------------------------------------
    // Initializies the system
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down
    //
    void shutdown();

    void findCollision(IDrawable &object);

    void defineContactInfo(IDrawable &obj_to_define_info, IDrawable &other_obj);
};
#endif // !COLLISIONDETECTOR_H
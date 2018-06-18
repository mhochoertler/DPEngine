//-----------------------------------------------------------------------------
// Camera.h
// Represents the view of the user
//-----------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

class IDrawable;

class Camera
{
  friend class Scene;

  private:
    //-------------------------------------------------------------------------
    // The central lookingpoint of the camera
    //
    Vector2D origin_;

    IDrawable* obj_to_follow_;

  public:
    //-------------------------------------------------------------------------
    // Constructors
    //
    Camera(int width, int height);

    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Camera();

    Vector2D getOrigin() const;

    int width_;

    int height_;

    void followObject(IDrawable* object);

    void update();
};
#endif // !CAMERA_H
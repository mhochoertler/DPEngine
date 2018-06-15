//-----------------------------------------------------------------------------
// Camera.h
// Represents the view of the user
//-----------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

class Camera
{
  friend class Scene;

  private:
    //-------------------------------------------------------------------------
    // The central lookingpoint of the camera
    //
    Vector2D origin_;

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
};
#endif // !CAMERA_H
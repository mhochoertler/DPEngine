#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include "Component.h"
#include "ComponentType.h"
#include "Vector2D.h"

class IDrawable;

typedef struct _BOX_
{
  Vector2D top_left_;
  Vector2D top_right_;
  Vector2D btm_left_;
  Vector2D btm_right_;
}Box;

class BoxCollider2D : public Component
{
  private:
    Vector2D top_left_;
    Vector2D top_right_;
    Vector2D btm_left_;
    Vector2D btm_right_;
    int width_;
    int height_;

    bool is_solid_;

  public:
    BoxCollider2D();
    BoxCollider2D(IDrawable* object);
    ~BoxCollider2D();

    void changeSize(int width, int height);

    void update();

    bool hasIntersection(BoxCollider2D &collider);

    bool isSolid() const;

    int getWidth()
    {
      return width_;
    }

    int getHeight()
    {
      return height_;
    }

    Box getBox();
};
#endif // !BOXCOLLIDER2D_H

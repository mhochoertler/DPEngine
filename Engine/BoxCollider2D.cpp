#include "BoxCollider2D.h"

#include <SDL.h>

#include "IDrawable.h"
#include "SystemManager.h"
#include "CollisionResolver.h"

BoxCollider2D::BoxCollider2D(IDrawable* object): Component(object), is_solid_(true)
{
  type_ = CMP_BOXCOL2D;

  //TODO: decouple from sprite
  width_ = object->getSprite()->width_;
  height_ = object->getSprite()->height_;

  update();
}

BoxCollider2D::BoxCollider2D()
{
  type_ = CMP_BOXCOL2D;
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::changeSize(int width, int height)
{
  width_ = width;
  height_ = height;

  update();
}

void BoxCollider2D::update()
{
  Vector2D center = parent_object_->getOrigin();

  top_left_ = { center.x - width_ / 2, center.y - height_ / 2 };
  top_right_ = { center.x + width_ / 2, center.y - height_ / 2 };
  btm_left_ = { center.x - width_ / 2, center.y + height_ / 2 };
  btm_right_ = { center.x + width_ / 2, center.y + height_ / 2 };
}

bool BoxCollider2D::hasIntersection(BoxCollider2D &collider)
{
  SDL_Rect rect1 = { top_left_.x, top_left_.y, width_, height_ };
  SDL_Rect rect2 = { collider.top_left_.x, collider.top_left_.y, collider.width_, collider.height_ };

  return static_cast<bool>(SDL_HasIntersection(&rect1, &rect2));
}

bool BoxCollider2D::isSolid() const
{
  return is_solid_;
}

Box BoxCollider2D::getBox()
{
  return Box{ top_left_, top_right_, btm_left_, btm_right_ };
}

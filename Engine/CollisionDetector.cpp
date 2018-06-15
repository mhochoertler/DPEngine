//-----------------------------------------------------------------------------
// CollisionDetector.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <SDL.h>

#include "CollisionDetector.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "IDrawable.h"

//-----------------------------------------------------------------------------
CollisionDetector::CollisionDetector()
{
  type_ = SYS_CDETECTOR;
}

//-----------------------------------------------------------------------------
CollisionDetector::~CollisionDetector()
{
}

//-----------------------------------------------------------------------------
int CollisionDetector::init()
{
  contact_info_ = new ContactInfo();

  std::cout << "[CollisionDetector]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void CollisionDetector::shutdown()
{

}

//-----------------------------------------------------------------------------
void CollisionDetector::findCollision(IDrawable &object)
{
  BoxCollider2D* CMP_BOXCOL2D = object.getComponent<BoxCollider2D>();
  if (!CMP_BOXCOL2D) return;

  //TODO: Implement Quadtree

  for (auto &pair : object.getScene()->objects_)
  {
    //TODO: separate map of objects with colliders
    BoxCollider2D* collider1 = object.getComponent<BoxCollider2D>();
    BoxCollider2D* collider2 = pair.second->getComponent<BoxCollider2D>();

    if (!collider2 || collider1 == collider2) continue;
    else if (collider1->hasIntersection(*collider2))
    {
      defineContactInfo(object, *pair.second);
      object.receiveCollision(*pair.second, contact_info_);

      defineContactInfo(*pair.second, object);
      pair.second->receiveCollision(object, contact_info_);
    }
  }
}

void CollisionDetector::defineContactInfo(IDrawable &obj_to_define_info, IDrawable &other_obj)
{
  BoxCollider2D* collider1 = obj_to_define_info.getComponent<BoxCollider2D>();
  BoxCollider2D* collider2 = other_obj.getComponent<BoxCollider2D>();

  Box box = collider1->getBox();
  Box box2 = collider2->getBox();

  SDL_Rect top = { box.btm_left_.x, box.btm_left_.y + 1, collider1->getWidth(), 1 };
  SDL_Rect btm = { box.top_left_.x, box.top_left_.y, collider1->getWidth(), 1 };
  SDL_Rect right = { box.btm_right_.x, box.btm_right_.y, 1, collider1->getHeight() };
  SDL_Rect left = { box.btm_left_.x - 1, box.btm_left_.y, 1, collider1->getHeight() };

  SDL_Rect o_obj = { box2.top_left_.x, box2.top_left_.y, collider2->getWidth(), collider2->getHeight() };

  bool cnt_top = false;
  bool cnt_btm = false;
  bool cnt_right = false;
  bool cnt_left = false;

  if (SDL_HasIntersection(&top, &o_obj))  cnt_top = true;
  if (SDL_HasIntersection(&btm, &o_obj))  cnt_btm = true;
  if (SDL_HasIntersection(&right, &o_obj))  cnt_right = true;
  if (SDL_HasIntersection(&left, &o_obj))  cnt_left = true;

  contact_info_->top_ = cnt_top;
  contact_info_->btm_ = cnt_btm;
  contact_info_->right_ = cnt_right;
  contact_info_->left_ = cnt_left;
}
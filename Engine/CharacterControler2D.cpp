#include "CharacterControler2D.h"

#include <SDL.h>
#include "IDrawable.h"
#include "InputHandler.h"
#include "SystemManager.h"
#include "KeyList.h"

//-----------------------------------------------------------------------------
CharacterControler2D::CharacterControler2D(IDrawable* object) 
                     : Component(object)
{
  type_ = CMP_CHARCONT2D;

  mScale_ = 60.f;

  accX_ = 0.3f * mScale_;
  accY_ = 0.4f * mScale_;
  decX_ = 0.5f * mScale_;
  maxSpeedX_ = 5.0f * mScale_;
  maxSpeedY_ = 10.0f * mScale_;
  jumpStartSpeedY_ = 7.0f * mScale_;

  speedX_ = 0.f;
  speedY_ = 0.f;

  isJumping_ = true;
  isMoving_ = false;
}

CharacterControler2D::CharacterControler2D()
{
  type_ = CMP_CHARCONT2D;
}

//-----------------------------------------------------------------------------
CharacterControler2D::~CharacterControler2D()
{

}

//-----------------------------------------------------------------------------
void CharacterControler2D::updatePosition()
{
  // Calculate new position 
  Uint32 updateTick = SDL_GetTicks();

  float secs_elapsed = (updateTick - parent_object_->getLastUpdate()) / 1000.0f;

  int posX = parent_object_->getOrigin().x + secs_elapsed * speedX_;
  int posY = parent_object_->getOrigin().y + secs_elapsed * speedY_;

  Vector2D new_pos = { posX, posY };
  parent_object_->setOrigin(new_pos);

  InputHandler* input_sys = SystemManager::instance()->getSubSystem<InputHandler>();

  if (input_sys->getKey(KEYBOARD_A)) moveLeft();
  if (input_sys->getKey(KEYBOARD_D)) moveRight();
  if (input_sys->getKey(KEYBOARD_SPACE)) jump();

  gravitate();
  if (!isMoving_) decelerate();
  else isMoving_ = false;
}

//-----------------------------------------------------------------------------
void CharacterControler2D::gravitate()
{
  speedY_ -= accY_;
  if (speedY_ > maxSpeedY_) speedY_ = maxSpeedY_;
}

//-----------------------------------------------------------------------------
void CharacterControler2D::decelerate()
{
  if (isMoving_) return;

  if (speedX_ < 0) speedX_ += decX_;
  if (speedX_ > 0) speedX_ -= decX_;

  // Deceleration may produce a speed that is greater than zero but
  // smaller than the smallest unit of deceleration. These lines ensure
  // that the player does not keep travelling at slow speed forever after
  // decelerating.
  if (speedX_ > 0 && speedX_ < decX_)
  {
    speedX_ = 0;
  }
  if (speedX_ < 0 && speedX_ > -decX_)
  {
    speedX_ = 0;
  }
}

//-----------------------------------------------------------------------------
void CharacterControler2D::collision(ContactInfo* info)
{
  // Ajust speed if there was collision
  if (info->btm_ && speedY_ < 0)
  {
    speedY_ = 0;
    isJumping_ = false;
  }
  if (info->top_ && speedY_ > 0)
  {
    speedY_ = 0;
  }
  if (info->right_ && speedX_ > 0)
  {
    speedX_ = 0;
  }
  if (info->left_ && speedX_ < 0)
  {
    speedX_ = 0;
  }
}

//-----------------------------------------------------------------------------
void CharacterControler2D::moveLeft()
{
  speedX_ -= accX_;
  isMoving_ = true;

  if (speedX_ < -maxSpeedX_)
  {
    speedX_ = -maxSpeedX_;
  }
}

//-----------------------------------------------------------------------------
void CharacterControler2D::moveRight()
{
  speedX_ += accX_;
  isMoving_ = true;

  if (speedX_ > maxSpeedX_)
  {
    speedX_ = maxSpeedX_;
  }
}

//-----------------------------------------------------------------------------
void CharacterControler2D::jump()
{
  if (!isJumping_)
  {
    isJumping_ = true;
    speedY_ = jumpStartSpeedY_;

    if (speedY_ < -maxSpeedY_)
    {
      speedY_ = -maxSpeedY_;
    }
  }
}

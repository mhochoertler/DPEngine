#ifndef CHARACTERCONTROLER2D_H
#define CHARACTERCONTROLER2D_H

#include "Component.h"
#include "ComponentType.h"
#include "CollisionDetector.h"
#include "Vector2D.h"

class IDrawable;

class CharacterControler2D : public Component
{
  private:
    float mScale_;
    float accX_, decX_;
    float accY_;
    float speedX_, speedY_;
    float maxSpeedX_, maxSpeedY_;
    float jumpStartSpeedY_;
    bool isJumping_;
    bool isMoving_;

  public:
    CharacterControler2D();
    CharacterControler2D(IDrawable* object);
    ~CharacterControler2D();

    void updatePosition();

    void decelerate();

    void gravitate();

    void collision(ContactInfo* info);

    void moveLeft();

    void moveRight();

    void jump();

};
#endif // !CHARACTERCONTROLER2D_H
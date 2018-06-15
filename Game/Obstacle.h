#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "IDrawable.h"
#include "BoxCollider2D.h"

class Obstacle : public IDrawable
{
  void start()
  {
    gameObject.addSprite("tile.png");
    gameObject.addComponent<BoxCollider2D>();
  }

  void onUpdate()
  {

  }

  void onCollision()
  {

  }
};
#endif // !OBSTACLE_H
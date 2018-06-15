//-----------------------------------------------------------------------------
// CollisionResolver.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <SDL.h>

#include "CollisionResolver.h"
#include "BoxCollider2D.h"
#include "IDrawable.h"

//-----------------------------------------------------------------------------
CollisionResolver::CollisionResolver()
{
  type_ = SYS_CRESOLVER;
}

//-----------------------------------------------------------------------------
CollisionResolver::~CollisionResolver()
{
}

//-----------------------------------------------------------------------------
int CollisionResolver::init()
{
  std::cout << "[CollisionResolver]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void CollisionResolver::shutdown()
{
}

//-----------------------------------------------------------------------------
void CollisionResolver::resolveCollision(IDrawable &self, IDrawable &colliding_object)
{
  //TODO: Fixing bullet-through-paper problem

  Vector2D target_position = self.getOrigin();
  Vector2D target_vector = target_position - self.getPositionAtLastFrame();
  double vector_length = sqrt(pow(target_vector.x, 2) + pow(target_vector.y, 2));

  if (vector_length == 0) return;

  self.setOrigin(self.getPositionAtLastFrame());

  double vecX = 0, vecY = 0;
  int segment = 0;

  // Correcting the position
  BoxCollider2D* collider1 = self.getComponent<BoxCollider2D>();
  BoxCollider2D* collider2 = colliding_object.getComponent<BoxCollider2D>();

  Vector2D tmp_position = self.getOrigin();
  Vector2D last_position;

  while (!collider1->hasIntersection(*collider2) && segment < vector_length)
  {
    last_position = tmp_position;

    vecY += target_vector.y / vector_length;
    vecX += target_vector.x / vector_length;

    //TODO: change world coordinates to float
    tmp_position = { last_position.x + static_cast<int>(round(vecX)), last_position.y + static_cast<int>(round(vecY)) };
    self.setOrigin(tmp_position);

    segment++;
  }

  self.setOrigin(last_position);
}

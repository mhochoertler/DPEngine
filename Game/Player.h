#ifndef PLAYER_H
#define PLAYER_H

#include "IDrawable.h"
#include "CharacterControler2D.h"
#include "BoxCollider2D.h"

class Player : public IDrawable
{
  void start()
  {
    gameObject.addSprite("player_default.png");
    gameObject.addComponent<CharacterControler2D>();
    gameObject.addComponent<BoxCollider2D>();
  }
  
  void onUpdate()
  {
    
  }

  void onCollision()
  {

  }
};
#endif // !PLAYER_H
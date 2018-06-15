//-----------------------------------------------------------------------------
// Game.h
//-----------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "AbstractGame.h"
#include "Player.h"
#include "Obstacle.h"

class Game : public AbstractGame
{
  void init()
  {
    //TODO: Implement functionallity to load predefined scenes at runtime

    Scene* myscene = createNewScene("MyScene");

    for (int x = -500; x < 500; x += 28)
    {
      myscene->addObject(*new Obstacle(), x, -200);
    }
    myscene->addObject((*new Player()), 0, 0);
  }
};
#endif //!GAME_H

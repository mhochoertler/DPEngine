//-----------------------------------------------------------------------------
// Game.h
//-----------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "AbstractGame.h"
#include "Player.h"
#include "Obstacle.h"
#include "Camera.h"

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

    myscene->addObject(*new Obstacle(), 300, -172);
    myscene->addObject(*new Obstacle(), 300, -90);
    myscene->addObject(*new Obstacle(), 0, -56);

    Player* player = new Player();
    myscene->getTargetCamera()->followObject(player);
    myscene->addObject((*player), 0, 56);
  }
};
#endif //!GAME_H

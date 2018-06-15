//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <Engine.h>

#include "game.h"

//-----------------------------------------------------------------------------
int main()
{
  AbstractGame* game = new Game();

  Engine::instance()->runGame(game);

  delete game;

  return 0;
}
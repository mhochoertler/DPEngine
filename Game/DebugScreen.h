//-----------------------------------------------------------------------------
// DebugScreen.cpp
//-----------------------------------------------------------------------------
#ifndef DEBUGSCREEN_H
#define DEBUGSCREEN_H

#include <SDL_ttf.h>
#include <string>

class Player;
class Level;
class Actor;
class Texture;

class DebugScreen
{
  private:
    bool visible_;

    Actor* actor_;

    TTF_Font* font_;

    SDL_Color color_;

    Texture* text_texture_;

    static DebugScreen* instance_;

    DebugScreen();

    std::string buildText();

  public:

    ~DebugScreen();

    void draw();

    void convertTextToTexture(std::string text, SDL_Color color);

    static DebugScreen* instance();

    void inspect(Actor* actor);

    void toggle();

};
#endif  // !DEBUGSCREEN_H

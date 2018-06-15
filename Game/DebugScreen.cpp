//-----------------------------------------------------------------------------
// DebugScreen.cpp
//-----------------------------------------------------------------------------
#include <sstream>

#include "DebugScreen.h"
#include "Graphics.h"
#include "Texture.h"
#include "Actor.h"

DebugScreen* DebugScreen::instance_ = 0;

//-----------------------------------------------------------------------------
DebugScreen::DebugScreen() : text_texture_(NULL), visible_(false)
{
  color_ = { 0, 0, 0, 0 };
  font_ = TTF_OpenFont("Assets/Fonts/FreeSans.ttf", 18);
  if (font_ == NULL)
  {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
  }
}

//-----------------------------------------------------------------------------
DebugScreen::~DebugScreen()
{
  TTF_CloseFont(font_);
  delete(text_texture_);
}

//-----------------------------------------------------------------------------
DebugScreen* DebugScreen::instance()
{
  if (instance_ == 0)
  {
    instance_ = new DebugScreen();
  }
  return instance_;
}

//-----------------------------------------------------------------------------
void DebugScreen::draw()
{
  SDL_Renderer* renderer = Graphics::instance()->getRenderer();

  convertTextToTexture(buildText(), color_);

  if (text_texture_ != NULL && visible_)
  {
    int width = text_texture_->getSize()->first;
    int height = text_texture_->getSize()->second;

    SDL_Rect position = { 0, 0, width, height };

    SDL_RenderCopy(renderer, text_texture_->getSDLTexture(),
      NULL, &position);
  }
}

//-----------------------------------------------------------------------------
void DebugScreen::convertTextToTexture(std::string text, SDL_Color color)
{
  if (text_texture_ != NULL) delete(text_texture_);

  //Render text surface
  SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font_, text.c_str(), color, 300);
  if (textSurface == NULL)
  {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }
  else
  {
    //Create texture from surface pixels
    SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(Graphics::instance()->getRenderer(), textSurface);
    if (sdl_texture == NULL)
    {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get image dimensions
      int width = textSurface->w;
      int height = textSurface->h;

      text_texture_ = new Texture(sdl_texture, width, height);
    }
    //Get rid of old surface
    SDL_FreeSurface(textSurface);
  }
}

//-----------------------------------------------------------------------------
void DebugScreen::inspect(Actor* actor)
{
  actor_ = actor;
}

//-----------------------------------------------------------------------------
void DebugScreen::toggle()
{
  if (visible_)
  {
    visible_ = false;
  }
  else visible_ = true;
}

//-----------------------------------------------------------------------------
std::string DebugScreen::buildText()
{
  std::stringstream text;

  text << "Col.Btm: " << actor_->getCollisionInfo()->collisionBtm << "\n"
    << "Col.Top: " << actor_->getCollisionInfo()->collisionTop << "\n"
    << "Col.Right: " << actor_->getCollisionInfo()->collisionRight << "\n"
    << "Col.Left: " << actor_->getCollisionInfo()->collisionLeft << "\n"

    << "Speed X: " << actor_->getMovementInfo()->speedX << "\n"
    << "Speed Y: " << actor_->getMovementInfo()->speedY << "\n";

  return text.str();
}
//-----------------------------------------------------------------------------
// Sprite.cpp
//-----------------------------------------------------------------------------
#include <SDL.h>

#include "Sprite.h"
#include "Texture.h"

//-----------------------------------------------------------------------------
Sprite::Sprite(Texture* texture) : texture_(texture)
{
  clip_ = new SDL_Rect();

  width_ = texture->getSize()->first;
  height_ = texture->getSize()->second;
}

//-----------------------------------------------------------------------------
Sprite::Sprite(Texture* texture, int clipX, int clipY, int width, int height) : 
            texture_(texture), is_clipped_(true)
{
  width_ = texture->getSize()->first;
  height_ = texture->getSize()->second;

  clip_->x = clipX;
  clip_->y = clipY;
  clip_->h = height;
  clip_->w = width;
}

//-----------------------------------------------------------------------------
Sprite::~Sprite()
{
  delete clip_;
}

//-----------------------------------------------------------------------------
SDL_Rect* Sprite::getClip()
{
  if(is_clipped_) return clip_;
  else return NULL;
}
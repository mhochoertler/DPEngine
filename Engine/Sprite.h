//-----------------------------------------------------------------------------
// Sprite.h
//-----------------------------------------------------------------------------
#ifndef SPRITE_H
#define SPRITE_H

struct SDL_Rect;
class Texture;

class Sprite
{
  private:
    SDL_Rect* clip_;

    bool is_clipped_ = false;

  public:
    Texture* texture_;

    int width_;

    int height_;

    Sprite(Texture* texture);

    Sprite(Texture* texture, int clipX, int clipY, int width, int height);

    ~Sprite();

    SDL_Rect* getClip();

};
#endif // !SPRITE_H

//-----------------------------------------------------------------------------
// Texture.h
// Wrapper for SDL_Textures
//-----------------------------------------------------------------------------
#ifndef TEXTURE_H
#define TEXTURE_H

#include <tuple>

struct SDL_Texture;

class Texture
{
  private:
    //-------------------------------------------------------------------------
    // SDL_Texture representing the image for rendering
    //
    SDL_Texture* texture_;

    //-------------------------------------------------------------------------
    // Stores the width and height of the texture
    //
    std::pair<int, int> size_;

  public:
    //-------------------------------------------------------------------------
    // Constructor
    //
    Texture(SDL_Texture* texture, int w, int h);

    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Texture();

    //-------------------------------------------------------------------------
    // Getter Methods
    //
    SDL_Texture* getSDLTexture();

    std::pair<int, int>* getSize();
};
#endif // !TEXTURE_H


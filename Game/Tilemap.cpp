//-----------------------------------------------------------------------------
// Tilemap.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>

#include "TextureLoader.h"
#include "Tilemap.h"
#include "Graphics.h"
#include "Camera.h"
#include "Actor.h"
#include "Tile.h"

//-----------------------------------------------------------------------------
Tilemap::Tilemap(int tile_size, Level &level, OPTIONS setting) : 
               tile_size_(tile_size), level_(&level), setting_(setting)
{
  //resizes the map to the given size
  map_.resize(level.getHeight() / tile_size);

  for (unsigned int i = 0; i < map_.size(); i++)
  {
    map_.at(i).resize(level.getWidth() / tile_size, NULL);
  }

  tiles_in_Y_ = level.getHeight() / tile_size - 1;
  tiles_in_X_ = level.getWidth() / tile_size - 1;

  level.addTilemap(this);
}

//-----------------------------------------------------------------------------
Tilemap::~Tilemap()
{
  //Deletes all loaded tiles
  if (!tile_pool_.empty())
  {
    std::map<int, Tile*>::iterator itr = tile_pool_.begin();
    while (itr != tile_pool_.end())
    {
      delete (itr->second);
      itr = tile_pool_.erase(itr); //used to get iterator to the next element
    }
  }
}

//-----------------------------------------------------------------------------
const int Tilemap::getTileSize()
{
  return tile_size_;
}

//-----------------------------------------------------------------------------
Tile* Tilemap::getTile(int y, int x)
{
  Tile* tile;

  if (y > tiles_in_Y_) y = tiles_in_Y_;
  if (x > tiles_in_X_) x = tiles_in_X_;

  tile = map_[y][x];

  return tile;
}

//-----------------------------------------------------------------------------
void Tilemap::draw(Camera* camera)
{
  // Draws just the seen tiles
  SDL_Rect dstrect;
  SDL_Texture* dsttexture;
  SDL_Rect* srcclip;

  SDL_Renderer* renderer = Graphics::instance()->getRenderer();

  SDL_Rect* camera_rect = camera->getRect();

  int startX = camera_rect->x / tile_size_;
  int startY = camera_rect->y / tile_size_;

  int endX = (camera_rect->x + camera_rect->w) / tile_size_;
  int endY = (camera_rect->y + camera_rect->h) / tile_size_;

  for (int y = startY; y <= endY; y++)
  {
    for (int x = startX; x <= endX; x++)
    {
      dstrect = { x * tile_size_, y * tile_size_, tile_size_, tile_size_ };

      if (getTile(y, x) != NULL)
      {
        dsttexture = map_[y][x]->getSprite()->texture_->getSDLTexture();
        srcclip = map_[y][x]->getSprite()->getClip();

        SDL_RenderCopy(renderer, dsttexture, srcclip, &dstrect);
      }
      if (setting_ == SHOW_GRID)
      {
        //Render grid
        SDL_SetRenderDrawColor(renderer, 0xD3, 0xD3, 0xD3, 0xAA);
        SDL_RenderDrawRect(renderer, &dstrect);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }
}

//-----------------------------------------------------------------------------
void Tilemap::createNewTile(Sprite sprite)
{
  Tile* new_tile = new Tile(sprite);

  if (tile_pool_.find(1) == tile_pool_.end())
  {
    tile_pool_[1] = new_tile;  //get tile_ID instead of 1
  }
}

//-----------------------------------------------------------------------------
void Tilemap::addTile(int tile_ID, Coordinate position)
{
  Tile* tile;

  try 
  {
    tile = tile_pool_.at(tile_ID);
  }
  catch (std::exception &e)
  {
    std::cout << "Tile ID not found" << std::endl;
    return;
  }

  int tileX = position.x / tile_size_;
  int tileY = position.y / tile_size_;

  if (tileX > tiles_in_X_) tileX = tiles_in_X_;
  if (tileY > tiles_in_Y_) tileY = tiles_in_Y_;

  map_[tileY][tileX] = tile;
}

//-----------------------------------------------------------------------------
void Tilemap::deleteTile(Coordinate position)
{
  int tileX = position.x / tile_size_;
  int tileY = position.y / tile_size_;

  if (tileX > tiles_in_X_) tileX = tiles_in_X_;
  if (tileY > tiles_in_Y_) tileY = tiles_in_Y_;

  map_[position.x / tile_size_][position.y / tile_size_] = NULL;
}
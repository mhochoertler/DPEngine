//-----------------------------------------------------------------------------
// Tilemap.cpp
// Class for creating a renderable tilemap
//-----------------------------------------------------------------------------
#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <map>

#include "Level.h"

class Camera;
class Tile;
class Actor;
class Sprite;

class Tilemap
{
  public:
    //-------------------------------------------------------------------------
    // Struct holding options for rendering
    //
    enum OPTIONS
    {
      NONE,
      SHOW_GRID,
    };

  private:
    //-------------------------------------------------------------------------
    // The size of each tile in the map
    //
    const int tile_size_;

    //-------------------------------------------------------------------------
    // Amount of tiles in X direction
    //
    int tiles_in_X_;

    //-------------------------------------------------------------------------
    // Amount of tiles in Y direction
    //
    int tiles_in_Y_;

    //-------------------------------------------------------------------------
    // The scene in which the tilemap is placed
    //
    Level* level_;

    //-------------------------------------------------------------------------
    // 2D-Vector representing a tile-based map
    //
    std::vector<std::vector<Tile*>> map_;

    //-------------------------------------------------------------------------
    // Stores every different tile
    //
    std::map<int, Tile*> tile_pool_;

    //-------------------------------------------------------------------------
    // Options for displaying the tilemap
    //
    OPTIONS setting_;

  public:
    //-------------------------------------------------------------------------
    // Constructor
    //
    Tilemap(int tile_size, Level &level, OPTIONS setting = NONE);

    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Tilemap();

    //-------------------------------------------------------------------------
    // Method for rendering to the scene
    //
    void draw(Camera* camera);

    //-------------------------------------------------------------------------
    // Creates a new tile and adds it to the tile pool
    //
    void createNewTile(Sprite sprite);

    //-------------------------------------------------------------------------
    // Adds the tile to the map
    //
    void addTile(int tile_ID, Coordinate position);

    //-------------------------------------------------------------------------
    // Deletes the tile from the map
    //
    void deleteTile(Coordinate position);

    //-------------------------------------------------------------------------
    // Gets the tile from a specific position in the tilemap
    //
    Tile* getTile(int x, int y);

    //-------------------------------------------------------------------------
    // Getter Methods
    //
    const int getTileSize();

};
#endif // !TILEMAP_H




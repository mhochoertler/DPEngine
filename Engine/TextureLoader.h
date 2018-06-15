//-----------------------------------------------------------------------------
// TextureLoader.h
// Loads and unloads game textures
//-----------------------------------------------------------------------------
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <map>

#include "System.h"

class Texture;

class TextureLoader : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Represents information about the loading status
    //
    typedef struct _LOADING_INFO_
    {
      std::string entry_path;
      bool entry_directory_found = true;
      int directories_searched = 0;
      int successful = 0;
      int failed = 0;
    }loading_info;

  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    TextureLoader();

    //-------------------------------------------------------------------------
    // Holds information about the loading status
    //
    loading_info info_;

    //-------------------------------------------------------------------------
    // Map holding all textures
    //
    std::map<std::string, Texture*> textures_;

    //-------------------------------------------------------------------------
    // Method for creating textures out of images
    //
    Texture* convertToTexture(std::string image_path);

    //-------------------------------------------------------------------------
    // Recursive function which loads all image files from an 
    // directory hirarchy
    //
    void loadTextures(std::string directory_path_);

    //-------------------------------------------------------------------------
    // Used for unloading all textures
    //
    void unloadTextures();

    //-------------------------------------------------------------------------
    // Prints information about the loading status
    //
    void printLoadingInfo();

    //-------------------------------------------------------------------------
    // Checks file against all supported file extensions
    //
    bool checkForFileExtension(std::string filename);

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~TextureLoader();

    //-------------------------------------------------------------------------
    // Returns texture based on the texture_name
    //
    Texture* getImage(std::string image_name);

    //-------------------------------------------------------------------------
    // Initializies the system and loads textures from given path
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down and unload all textures
    //
    void shutdown();
};
#endif // !TEXTUREMANAGER_H


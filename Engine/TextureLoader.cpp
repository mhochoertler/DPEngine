//-----------------------------------------------------------------------------
// TextureLoader.cpp
//-----------------------------------------------------------------------------
#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <windows.h> //Not portable

#include "TextureLoader.h"
#include "SystemManager.h"
#include "Texture.h"

#include "Renderer.h"

//-----------------------------------------------------------------------------
TextureLoader::TextureLoader()
{
  type_ = SYS_TEXLOADER;
}

//-----------------------------------------------------------------------------
TextureLoader::~TextureLoader()
{
}

//-----------------------------------------------------------------------------
int TextureLoader::init()
{
  std::string directory_path = "Assets/Images/";

  loadTextures(directory_path);
  printLoadingInfo();

  std::cout << "[TextureLoader]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void TextureLoader::shutdown()
{
  unloadTextures();
}

//-----------------------------------------------------------------------------
Texture* TextureLoader::convertToTexture(std::string image_path)
{
  Renderer* renderer = SystemManager::instance()->getSubSystem<Renderer>();

  SDL_Texture* sdlTexture = NULL;
  int width;
  int height;

  //Load image at specified path and converts it to SDL_Texture
  sdlTexture = IMG_LoadTexture(renderer->getRenderer(), image_path.c_str());

  if (sdlTexture == NULL)
  {
    return NULL;
  }
  else
  {
    //Get width and hight of texture
    SDL_QueryTexture(sdlTexture, NULL, NULL, &width, &height);
    Texture* texture = new Texture(sdlTexture, width, height);
    return texture;
  }
}

//-----------------------------------------------------------------------------
void TextureLoader::unloadTextures()
{
  //Deletes all loaded textures
  if (!textures_.empty()) 
  {
    std::map<std::string, Texture*>::iterator itr = textures_.begin();
    while (itr != textures_.end())
    {
      delete (itr->second);
      itr = textures_.erase(itr); //used to get iterator to the next element
    }
  }
}

//-----------------------------------------------------------------------------
Texture* TextureLoader::getImage(std::string image_name)
{
  if(textures_.find(image_name) == textures_.end())
  {
    std::cout << "-> Wrong image name: " << image_name << std::endl;
    return NULL;
  }

  return textures_[image_name];
}

//-----------------------------------------------------------------------------
void TextureLoader::loadTextures(std::string directory_path)
{
  Texture* loaded_texture = NULL;

  WIN32_FIND_DATA FindFileData;
  HANDLE hfind;

  info_.entry_path = directory_path;

  hfind = FindFirstFile((directory_path + "/*").c_str(), &FindFileData);
  if (hfind == INVALID_HANDLE_VALUE)
  {
    info_.entry_directory_found = false;
    std::cout << "[ERROR] Directory not found: " << directory_path << std::endl;
  }
  else
  {
    do
    {
      std::string file_name = FindFileData.cFileName;

      if (file_name[0] == '.') continue;

      //if the found file is a directory
      else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        info_.directories_searched++;
        loadTextures(directory_path + file_name + "/");
      }

      //if the found file has a not supported file extension
      else if (!checkForFileExtension(file_name)) continue;

      else 
      {
        std::string file_name = FindFileData.cFileName;
        std::string full_file_name = directory_path + file_name;

        loaded_texture = convertToTexture(full_file_name);
        if (loaded_texture != NULL)
        {
          //checks for double named files
          if(textures_.find(file_name) == textures_.end())
          {
            info_.successful++;
            textures_[file_name] = loaded_texture;
            std::cout << "[SUCCESS] Loaded image: " << full_file_name << std::endl;
          }
          else
          {
            info_.failed++;
            std::cout << "[ERROR] Name is already taken: " << full_file_name
              << std::endl;
          }
        }
        else 
        {
          info_.failed++;
          std::cout << "[ERROR] Unable to load image: " << full_file_name
                    << std::endl;
        }
      }
    } while (FindNextFile(hfind, &FindFileData));
  }
  FindClose(hfind);
}

//-----------------------------------------------------------------------------
bool TextureLoader::checkForFileExtension(std::string filename)
{
  std::string file_extension = filename.substr(filename.find('.'));

  if (file_extension == ".png" || 
      file_extension == ".jpeg" || 
      file_extension == ".bmp")
  {
    return true;
  }
  else return false;
}

//-----------------------------------------------------------------------------
void TextureLoader::printLoadingInfo()
{
  std::cout << "SUCCESSFUL: " << info_.successful << "  ";
  std::cout << "FAILED: " << info_.failed << "  ";
  std::cout << "DIRECTORIES: " << info_.directories_searched << std::endl;
  std::cout << std::endl;
}
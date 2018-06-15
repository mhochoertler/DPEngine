//-----------------------------------------------------------------------------
// Scene.h
// Class representing a scene in the game that holds gameobjects
//-----------------------------------------------------------------------------
#ifndef SCENE_H
#define SCENE_H

#include <map>

class Camera;
class Texture;
struct SDL_Texture;
struct SDL_Rect;
class IDrawable;
class Renderer;

class Scene
{
  friend class CollisionResolver;
  friend class CollisionDetector;
  friend class GameManager;

  private:
    //-------------------------------------------------------------------------
    // The amount of objects in the scene
    //
    unsigned long object_count_;

    //-------------------------------------------------------------------------
    // The name of the scene
    //
    std::string name_;

    //-------------------------------------------------------------------------
    // The camera through which the scene gets rendered
    //
    Camera* target_camera_;

    std::map<std::string, IDrawable*> objects_;

    //-------------------------------------------------------------------------
    // Used for updating all objects in the scene
    //
    void update();

  public:
    //-------------------------------------------------------------------------
    // Constructor
    //
    Scene();

    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Scene();

    //-------------------------------------------------------------------------
    // Method for rendering all world objects to the blank texture
    //
    void draw(Renderer* system) const;

    //-------------------------------------------------------------------------
    // Getter Methods
    //
    int getObjectCount() const;

    Camera* getTargetCamera() const;

    void addObject(IDrawable &object, int x, int y);

    bool isInView(IDrawable* object) const ;
};
#endif // !SCENE_H


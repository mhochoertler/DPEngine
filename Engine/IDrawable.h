#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <string>
#include <map>
#include <iostream>

#include "ComponentType.h"
#include "CollisionDetector.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "KeyList.h"

class Scene;
class Renderer;
class Component;
class Camera;

class IDrawable
{
  friend class Scene;

  private:
    Sprite* sprite_;
    Vector2D origin_;
    Vector2D position_at_last_frame_;

    std::string name_;

    Scene* scene_;

    std::map<ComponentType, Component*> components_;

    std::string getObjectName() const;

    void draw(Renderer* system, Camera* camera);

    float last_update_time_;

    IDrawable(const IDrawable &original);

  protected:
    IDrawable &gameObject = *this;

    InputHandler &input;

  public:
    IDrawable();
    virtual ~IDrawable();

    virtual void start() = 0;

    void update();

    void receiveCollision(IDrawable &colliding_object, ContactInfo* info);

    virtual void onCollision() = 0;

    virtual void onUpdate() = 0;

    template <class T> T* addComponent()
    {
      Component* cmp = new T(this);
      components_[cmp->getType()] = cmp;

      return dynamic_cast<T*>(cmp);
    }

    Sprite const* getSprite() const;
    Vector2D getOrigin() const;
    Vector2D getPositionAtLastFrame() const;
    Scene const* getScene() const;

    template <class T> T* getComponent()
    {
      T cmp = T();

      if (components_.find(cmp.getType()) != components_.end())
      {
        return dynamic_cast<T*>(components_[cmp.getType()]);
      }
      else return NULL;
    }

    void setOrigin(Vector2D new_origin);

    float getLastUpdate() const;

    void addSprite(std::string texture_name);

    void rename(std::string object_name);

};
#endif // !IDRAWABLE_H

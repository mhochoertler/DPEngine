#include "IDrawable.h"

#include <sstream>
#include <tuple>

#include "SystemManager.h"
#include "InputHandler.h"
#include "CollisionResolver.h"
#include "TextureLoader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Scene.h"
#include "Component.h"
#include "CharacterControler2D.h"
#include "BoxCollider2D.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
IDrawable::IDrawable() : sprite_(NULL), name_(""),
                         input(*SystemManager::instance()->getSubSystem<InputHandler>())
{
  components_[CMP_BOXCOL2D] = NULL;
  components_[CMP_CHARCONT2D] = NULL;
}

//-----------------------------------------------------------------------------
IDrawable::~IDrawable()
{
  for (auto &pair : components_)
  {
    delete pair.second;
  }
}

//-----------------------------------------------------------------------------
void IDrawable::receiveCollision(IDrawable &colliding_object, ContactInfo* info)
{
  if (colliding_object.getComponent<BoxCollider2D>()->isSolid()) 
  {
    SystemManager::instance()->getSubSystem<CollisionResolver>()->resolveCollision(*this, colliding_object);
    SystemManager::instance()->getSubSystem<CollisionDetector>()->defineContactInfo(*this, colliding_object);

    //TODO: loose coupling of components
    CharacterControler2D* CMP_CHARCONT2D = getComponent<CharacterControler2D>();
    if (CMP_CHARCONT2D) CMP_CHARCONT2D->collision(info);
  }

  onCollision();
}

//-----------------------------------------------------------------------------
void IDrawable::update()
{
  position_at_last_frame_ = origin_;

  //TODO: update all components throught interface designed method to reduce code

  if (components_[CMP_CHARCONT2D])
  {
    getComponent<CharacterControler2D>()->updatePosition();
  }

  onUpdate();

  SystemManager::instance()->getSubSystem<CollisionDetector>()->findCollision(*this);

  last_update_time_ = static_cast<float>(SDL_GetTicks());
}

//-----------------------------------------------------------------------------
void IDrawable::draw(Renderer* system, Camera* camera)
{
  SDL_Rect dstrect;
  Vector2D render_position;

  render_position.x = camera->width_ / 2 + (origin_.x - camera->getOrigin().x);
  render_position.y = camera->height_ / 2 + (camera->getOrigin().y - origin_.y);

  dstrect.x = render_position.x - sprite_->width_ / 2;
  dstrect.y = render_position.y - sprite_->height_ / 2;
  dstrect.w = sprite_->width_;
  dstrect.h = sprite_->height_;

  SDL_RenderCopy(system->getRenderer(), sprite_->texture_->getSDLTexture(),
                 NULL, &dstrect);
}

//-----------------------------------------------------------------------------
std::string IDrawable::getObjectName() const
{
  return name_;
}

//-----------------------------------------------------------------------------
Sprite const* IDrawable::getSprite() const
{
  return sprite_;
}

//-----------------------------------------------------------------------------
Vector2D IDrawable::getOrigin() const
{
  return origin_;
}

//-----------------------------------------------------------------------------
Vector2D IDrawable::getPositionAtLastFrame() const
{
  return position_at_last_frame_;
}

//-----------------------------------------------------------------------------
Scene const* IDrawable::getScene() const
{
  return scene_;
}

//-----------------------------------------------------------------------------
float IDrawable::getLastUpdate() const
{
  return last_update_time_;
}

//-----------------------------------------------------------------------------
void IDrawable::addSprite(std::string texture_name)
{
  Texture* texture = SystemManager::instance()->getSubSystem<TextureLoader>()->getImage(texture_name);

  if (texture != NULL)
  {
    sprite_ = new Sprite(texture);
  }
}

//-----------------------------------------------------------------------------
void IDrawable::rename(std::string object_name)
{
  name_ = object_name;
}

//-----------------------------------------------------------------------------
void IDrawable::setOrigin(Vector2D new_origin)
{
  origin_ = new_origin;

  BoxCollider2D* CMP_BOXCOL2D = getComponent<BoxCollider2D>();
  if (CMP_BOXCOL2D) CMP_BOXCOL2D->update();
}
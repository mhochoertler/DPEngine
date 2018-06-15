//-----------------------------------------------------------------------------
// InputHandler.cpp
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <SDL.h>

#include "InputHandler.h"

SDL_Event event_;
const Uint8* keystate_;

//-----------------------------------------------------------------------------
InputHandler::InputHandler()
{
  type_ = SYS_INPUT;
}

//-----------------------------------------------------------------------------
InputHandler::~InputHandler()
{
}

//-----------------------------------------------------------------------------
int InputHandler::init()
{
  keystate_ = SDL_GetKeyboardState(NULL);
  createKeyMapping();

  std::cout << "[InputHandler]: Initialization successfull" << std::endl;

  return 0;
}

//-----------------------------------------------------------------------------
void InputHandler::shutdown()
{
}

//-----------------------------------------------------------------------------
void InputHandler::checkForInput()
{
  input_.clear();

  // Handles events on queue
  while (SDL_PollEvent(&event_) != 0)
  {
    // User requests quit
    if (event_.type == SDL_QUIT)
    {
      input_.push_back(mapping_[WINDOW_QUIT]);
    }
  }

  if (keystate_[SDL_SCANCODE_W]) input_.push_back(mapping_[KEYBOARD_W]);

  if (keystate_[SDL_SCANCODE_A]) input_.push_back(mapping_[KEYBOARD_A]);

  if (keystate_[SDL_SCANCODE_S]) input_.push_back(mapping_[KEYBOARD_S]);

  if (keystate_[SDL_SCANCODE_D]) input_.push_back(mapping_[KEYBOARD_D]);

  if (keystate_[SDL_SCANCODE_SPACE]) input_.push_back(mapping_[KEYBOARD_SPACE]);

  if (keystate_[SDL_SCANCODE_F1]) input_.push_back(mapping_[KEYBOARD_F1]);

}

//-----------------------------------------------------------------------------
void InputHandler::createKeyMapping()
{
  for (int index = 0; index < NUMB_KEYS; index++)
  {
    mapping_[static_cast<Key>(index)] = static_cast<Key>(index);
  }
}

//-----------------------------------------------------------------------------
void InputHandler::changeKeyMapping(Key key1, Key key2)
{
  mapping_[key1] = key2;
  mapping_[key2] = key1;
}

//-----------------------------------------------------------------------------
bool InputHandler::getKey(Key key)
{
  bool is_pressed = false;

  for (Key pressed_key : input_)
  {
    if (pressed_key == key) is_pressed = true;
  }

  return is_pressed;
}
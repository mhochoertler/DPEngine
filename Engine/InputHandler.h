//-----------------------------------------------------------------------------
// InputHandler.h
// Returns keys based on the userinput
//-----------------------------------------------------------------------------
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <map>

#include "KeyList.h"
#include "System.h"

class InputHandler : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Indirect mapping of keys
    //
    std::map<Key, Key> mapping_;

    //-------------------------------------------------------------------------
    // Keystrokes at this frame
    //
    std::vector<Key> input_;

    //-------------------------------------------------------------------------
    // Creates the internal key mapping
    //
    void createKeyMapping();

    //-------------------------------------------------------------------------
    // Constructor
    //
    InputHandler();

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~InputHandler();

    //-------------------------------------------------------------------------
    // Gets a list of keys based on the users input and saves it for later usage
    //
    void checkForInput();

    //-------------------------------------------------------------------------
    // Changes the internal key-mapping of the inputhandler
    //
    void changeKeyMapping(Key key1, Key key2);

    //-------------------------------------------------------------------------
    // Initializies the system
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down
    //
    void shutdown();

    bool getKey(Key key);
};
#endif // !INPUTHANDLER_H

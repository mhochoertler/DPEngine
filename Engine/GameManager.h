//-----------------------------------------------------------------------------
// GameManager.h
// Manager used for executing the gameloop
//-----------------------------------------------------------------------------
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class AbstractGame;

class GameManager
{
  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    GameManager();

    //-------------------------------------------------------------------------
    // Indicates the current gamestate
    //
    bool is_running_;

    //-------------------------------------------------------------------------
    // Used for singleton implementation
    //
    static GameManager* instance_;

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~GameManager();

    //-------------------------------------------------------------------------
    // Executes the game loop
    //
    void startGameloop(AbstractGame* game);

    //-------------------------------------------------------------------------
    // Ends the game loop
    //
    void stopGameloop();

    //-------------------------------------------------------------------------
    // Deals with the userinput
    //
    void handleInput();

    //-------------------------------------------------------------------------
    // Gets an instance of the class
    //
    static GameManager* instance();
};
#endif // !GAMEMANAGER_H


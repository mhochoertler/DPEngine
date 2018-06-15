//-----------------------------------------------------------------------------
// MainTimer.h
// Represents time in the engine
//-----------------------------------------------------------------------------
#ifndef MAINTIMER_H
#define MAINTIMER_H

#include "System.h"

class MainTimer : public System
{
  friend class SystemManager;

  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    MainTimer();

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~MainTimer();

    //-------------------------------------------------------------------------
    // Initializies the system
    //
    int init();

    //-------------------------------------------------------------------------
    // Shuts the system down
    //
    void shutdown();
};
#endif // !MAINTIMER_H

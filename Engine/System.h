//-----------------------------------------------------------------------------
// System.h
//-----------------------------------------------------------------------------
#ifndef SYSTEM_H
#define SYSTEM_H

#include "SystemType.h"

class System
{
  protected:
    SystemType type_;

  public:
    //-------------------------------------------------------------------------
    // Constructor
    //
    System();

    //-------------------------------------------------------------------------
    // Destructor
    //
    virtual ~System();

    //-------------------------------------------------------------------------
    // Pure virtual method for initializing a system
    //
    virtual int init() = 0;

    //-------------------------------------------------------------------------
    // Pure virtual method for shuting down a system
    //
    virtual void shutdown() = 0;

    SystemType getType() const;
};
#endif // !SYSTEM_H

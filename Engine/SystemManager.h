//-----------------------------------------------------------------------------
// SystemManger.h
// Used for creating and destroying subsystems of the engine
//-----------------------------------------------------------------------------
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <map>

#include "SystemType.h"

class System;

class SystemManager
{
  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    SystemManager();

    //-------------------------------------------------------------------------
    // Holds all subsystems necessary for the engine
    //
    std::map<SystemType, System*> sub_systems_;

    //-------------------------------------------------------------------------
    // Used for singelton implementation
    //
    static SystemManager* instance_;

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~SystemManager();

    //-------------------------------------------------------------------------
    // Creates a new subsystem and inits it
    //
    int createSubSystem(SystemType type);

    //-------------------------------------------------------------------------
    // Shuts the subsystem down and deletes it
    //
    void deleteSubSystem(SystemType type);

    //-------------------------------------------------------------------------
    // Returns a previously created subsystem  
    //
    template<class T> T* getSubSystem()
    {
      T sys = T();

      if (sub_systems_.find(sys.getType()) != sub_systems_.end())
      {
        return dynamic_cast<T*>(sub_systems_[sys.getType()]);
      }
      return NULL;
    }

    //-------------------------------------------------------------------------
    // Returns a static instance
    //
    static SystemManager* instance();
};
#endif // !SYSTEMMANAGER_H

//-----------------------------------------------------------------------------
// ResourceManager.h
// Keeps track of all used resources
//-----------------------------------------------------------------------------
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager
{
  private:
    //-------------------------------------------------------------------------
    // Constructor
    //
    ResourceManager();

    //-------------------------------------------------------------------------
    // Used for Singleton implementation
    //
    static ResourceManager* instance_;

  public:
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~ResourceManager();

    //-------------------------------------------------------------------------
    // Returns an static instance
    //
    static ResourceManager* instance();
};
#endif // !RESOURCEMANAGER_H

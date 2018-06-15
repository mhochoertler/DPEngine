//-----------------------------------------------------------------------------
// SystemType.h
// Defines all subsystem types
//-----------------------------------------------------------------------------
#ifndef SYSTEMTYPE_H
#define SYSTEMTYPE_H

enum SystemType
{
  SYS_SDL,        //has to be the first one
  SYS_RENDERER,
  SYS_INPUT,
  SYS_TEXLOADER,
  SYS_TIMER,  
  SYS_CRESOLVER,
  SYS_CDETECTOR,

  SYS_MAX,        //has to be the last one!
};
#endif // !SYSTEMTYPE_H

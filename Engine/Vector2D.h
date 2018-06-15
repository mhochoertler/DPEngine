//-----------------------------------------------------------------------------
// Vector2D.h
// Represents a point in the scene
//-----------------------------------------------------------------------------
#ifndef VECTOR2D_H
#define VECTOR2D_H

typedef struct _VECTOR2D_
{
  int x;
  int y;

  _VECTOR2D_() {}

  _VECTOR2D_(int x_, int y_)
  {
    x = x_;
    y = y_;
  }

  _VECTOR2D_ operator+(const _VECTOR2D_& a) const
  {
    return _VECTOR2D_(a.x + x, a.y + y);
  }

  _VECTOR2D_ operator-(const _VECTOR2D_& a) const
  {
    return _VECTOR2D_(x - a.x, y - a.y);
  }
}Vector2D;

#endif // !VECTOR2D_H
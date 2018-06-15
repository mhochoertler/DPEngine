//-----------------------------------------------------------------------------
// PerlinNoise.h
// Used for getting a random height-map
//-----------------------------------------------------------------------------
#ifndef PERLINNOISE_H
#define PERLINNOISE_H

class PerlinNoise
{
  private:
    long seed_;

    float random(int x, int range);
    float CosinInterpolation(float a, float b, float x);

  public:
    PerlinNoise(long seed);
    ~PerlinNoise();

    int getNoise(int x, int range);
};
#endif // PERLINNOISE_H
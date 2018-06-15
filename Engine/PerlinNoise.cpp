//-----------------------------------------------------------------------------
// PerlinNoise.cpp
//-----------------------------------------------------------------------------
#include <random>
#include <algorithm>
#include <math.h>

#include "PerlinNoise.h"

const float PI = 3.1415927;

//-----------------------------------------------------------------------------
PerlinNoise::PerlinNoise(long seed) : seed_(seed)
{

}

//-----------------------------------------------------------------------------
PerlinNoise::~PerlinNoise()
{

}

//-----------------------------------------------------------------------------
int PerlinNoise::getNoise(int x, int range)
{
    int chunksize = 45;

    float noise = 0;

    range /= 2;

    while (chunksize > 0)
    {
        int chunkindex = x / chunksize;
        float prog = (x % chunksize) / ((float)chunksize);

        float left_random = random(chunkindex, range);
        float right_random = random(chunkindex + 1, range);

        noise += CosinInterpolation(left_random, right_random, prog);

        chunksize /= 2;
        range /= 2;

        range = std::max(1, range);
    }

    return (int)round(noise);
}

//-----------------------------------------------------------------------------
float PerlinNoise::random(int x, int range)
{
    return ((x + seed_) ^ 5) % range;
}

//-----------------------------------------------------------------------------
float PerlinNoise::CosinInterpolation(float a, float b, float x)
{
    float ft = x * PI;
    float f = (1 - cos(ft)) * .5;

    return a * (1 - f) + b * f;
}
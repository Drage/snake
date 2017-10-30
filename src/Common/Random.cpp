
#include "Random.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits>

long seed = 0;

void Random::SetSeed()
{
	seed = (long)time(NULL);
	srand(seed);
}

void Random::SetSeed(long randomSeed)
{
	seed = randomSeed;
	srand(seed);
}

float Random::Float()
{
	if (seed == 0) 
		SetSeed();
	
	return rand() / (float)RAND_MAX;
}

float Random::Float(float min, float max)
{
	if (seed == 0) 
		SetSeed();
	
	return (rand() / (float)RAND_MAX) * (max - min) + min;
}

int Random::Int(int min, int max)
{
	if (seed == 0) 
		SetSeed();
	
	return rand() % (max - min) + min;
}

bool Random::Bool()
{
	if (seed == 0) 
		SetSeed();
	
	return rand() % 2 == 0;
}

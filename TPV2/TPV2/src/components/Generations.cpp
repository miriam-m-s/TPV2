#include "Generations.h"
#include "../sdlutils/SDLUtils.h"

Generations::Generations(int g):numgenerations(g)
{
	
}

int Generations::getnumgenerations()
{
	return numgenerations;
}

void Generations::changenumgenerations(int s)
{
	numgenerations = s;
}

void Generations::restagenerations()
{
	numgenerations--;
}



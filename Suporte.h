#ifndef SUPORTE_H
#define SUPORTE_H

#include <Math.h>

enum Tipo 
{
	PORCO, VACA, OVELHA, POVELHA, GRAMA, TERRA, PEDRA, TNT, TIJOLO, JOINT, CAKE
};

struct IntVec2
{
	IntVec2(){};

	/// Construct using coordinates.
	IntVec2(int x, int y) : x(x), y(y) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0; y = 0; }

	/// Set this vector to some specified coordinates.
	void Set(int x_, int y_) { x = x_; y = y_; }

	int x,y;
};

#endif
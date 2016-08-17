#pragma once

#include "3DShape\3DShape.h"
#include "Mixin\HaveVertex.h"
#include "Wall\Wall.h"

class CLabyrinth
	: public CIdentity3DShape
{
public:
	CLabyrinth();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		BuildLabyrinth(const std::vector<CWall> & walls);
//////////////////////////////////////////////////////////////////////
// Data
public:

};
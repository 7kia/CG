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
	void		AddWall(PWall pWall);
	void		BuildLabyrinth(const std::vector<PWall> & walls);
//////////////////////////////////////////////////////////////////////
// Data
private:
	size_t		m_indexCount = 0;
};
#pragma once

#include "3DShape\3DShape.h"
#include "3DShape\Composite3DShape.h"
#include "Mixin\HaveVertex.h"
#include "Wall\Wall.h"
#include <array>


class CLabyrinthLevel
	: public CIdentity3DShape
{
public:
	CLabyrinthLevel();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		AddWall(PWall pWall);

	void		ReallocateMemory();
//////////////////////////////////////////////////////////////////////
// Data
private:
	size_t		m_indexCount = 0;
};

class CLabyrinth
	: public ÑComposite3DShape
{
public:
	CLabyrinth();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		AddWall(PWall pWall, size_t index);
	void		ReallocateMemory();
//////////////////////////////////////////////////////////////////////
// Data
private:
};
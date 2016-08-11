#pragma once

#include "../Actor.h"
#include "../../2DShape/2DRectangleCollision.h"
#include "WallView.h"

class CWall final
	: public IActor
	, public CTransformable
	, public IHavePointerToWallViewType
{
public:
	CWall();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IActor
	void							Draw() const override;
	void							Update(float deltaTime) override;
	//--------------------------------------------
	// IHavePointerToWallViewType
	void							SetType(const CWallViewType* type) override;
	const CWallViewType*			GetType() const override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
private:
	CWallView				m_visual;
	C2DRectangleCollision	m_collision;
};
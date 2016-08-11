#pragma once

#include "../Actor.h"
#include "../../2DShape/2DRectangleCollision.h"
#include "WallView.h"

class CWall final
	: public IActor
	, public CTransformable
	, public IHavePointerToWallViewType
	, public IHaveVisiblePart
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
	// IHaveVisiblePart
	void							SetVisible(unsigned index, bool value) override;
	bool							GetVisible(unsigned index) const override;

	void							CheckVisibleIndex(unsigned index) const override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
private:
	CWallView						m_visual;
	C2DRectangleCollision			m_collision;
};
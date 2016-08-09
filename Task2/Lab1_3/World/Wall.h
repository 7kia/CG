#pragma once

#include "../Shape/Rectangle.h"
#include <array>

namespace WallSpace
{
	static const float SIZE = 2.f;
}

class CWall final
	: public ÑCompositeShape
{
public:
	CWall();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	void					Draw() const override final;
	//--------------------------------------------

	void					SetVisible(uint index, bool value);
	bool					GetVisible(uint index) const;

	void					CheckVisibleIndex(uint index) const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::array<bool, 6>		m_visible;
};

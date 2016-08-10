#pragma once

#include "../Mixin/Drawable.h"
#include "3DShape.h"
#include <vector>


class ÑComposite3DShape 
	: public I3DShape
{
public:
	ÑComposite3DShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// I3DShape
	void					Draw() const override;
	//--------------------------------------------
private:
	void					CheckVertexIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};
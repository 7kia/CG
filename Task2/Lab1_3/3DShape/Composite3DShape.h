#pragma once

#include "3DShape.h"
#include <vector>


class �Composite3DShape 
	: public C3DShape
{
public:
	�Composite3DShape();
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
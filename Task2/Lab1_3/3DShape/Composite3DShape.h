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
	IBodyUniquePtr			GetShape(size_t index);// shape can will be changed
	void					CheckVertexIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};
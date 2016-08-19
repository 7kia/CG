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

	IBodySharedPtr			GetShape(size_t index);// shape can will be changed
	const IBodySharedPtr	GetShape(size_t index) const;// shape can will be changed

	size_t					GetAmountShapes() const;
private:
	void					CheckVertexIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodySharedPtr>		m_shapes;
};
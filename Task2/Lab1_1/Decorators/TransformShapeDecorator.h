#pragma once

#include "AbstractShapeDecorator.h"
#include <glm/mat3x3.hpp>

class CTransformShapeDecorator : public CAbstractShapeDecorator
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void Update(float deltaTime);
	void Draw()const;
	//--------------------------------------------

	void SetTransform(const glm::mat4 &transform);
	void ApplyTrasformToVertex(size_t index);
//////////////////////////////////////////////////////////////////////
// Data
private:
	glm::mat4 m_transform;
};
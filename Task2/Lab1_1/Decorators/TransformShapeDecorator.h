#pragma once

#include "AbstractShapeDecorator.h"

class CTransformShapeDecorator : public CAbstractShapeDecorator
{
public:
	void Update(float deltaTime);
	void Draw()const;

	void SetTransform(const glm::mat4 &transform);

private:
	glm::mat4 m_transform;
};
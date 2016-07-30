#include "stdafx.h"
#include "TransformShapeDecorator.h"


void CTransformShapeDecorator::Update(float deltaTime)
{
	CAbstractShapeDecorator::Update(deltaTime);
}

void CTransformShapeDecorator::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));
	CAbstractShapeDecorator::Draw();
	glPopMatrix();
}

void CTransformShapeDecorator::SetTransform(const glm::mat4 &transform)
{
	m_transform = transform;
}

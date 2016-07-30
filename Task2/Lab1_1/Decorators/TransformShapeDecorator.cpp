#include "stdafx.h"
#include "TransformShapeDecorator.h"


void CTransformShapeDecorator::Update(float deltaTime)
{
	UpdateChild(deltaTime);
}

void CTransformShapeDecorator::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));
	DrawChild();
	glPopMatrix();
}

void CTransformShapeDecorator::SetTransform(const glm::mat4 &transform)
{
	m_transform = transform;
}

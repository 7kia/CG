#include "stdafx.h"
#include "Transformable.h"

CTransformable::CTransformable()
	: ITransformable()
{
}

void CTransformable::SetTransform(const glm::mat4 & transform)
{
	m_transform = transform;
}

glm::mat4 CTransformable::GetTransform() const
{
	return m_transform;
}

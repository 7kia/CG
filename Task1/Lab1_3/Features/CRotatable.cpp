#include "stdafx.h"
#include "CRotatable.h"

float CRotatable::GetRotation() const
{
	return m_rotation;
}

void CRotatable::SetRotation(float rotation)
{
	m_rotation = rotation;
}

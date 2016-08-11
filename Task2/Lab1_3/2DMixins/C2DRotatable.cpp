#include "stdafx.h"
#include "C2DRotatable.h"

float C2DRotatable::GetRotation() const
{
	return m_rotation;
}

void C2DRotatable::SetRotation(float rotation)
{
	m_rotation = rotation;
}

#include "stdafx.h"
#include "WallType.h"

void CWallType::SetTexture(const std::string & texturePath)
{
	m_texture = LoadTexture2DFromBMP(texturePath);
}

CTexture2D* CWallType::GetTexture() const
{
	return m_texture.get();
}

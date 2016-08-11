#include "stdafx.h"
#include "../../stdafx.h"
#include "WallType.h"

void CWallViewType::SetTexture(const std::string & texturePath)
{
	m_texture = LoadTexture2DFromBMP(texturePath);
}

CTexture2D* CWallViewType::GetTexture() const
{
	return m_texture.get();
}

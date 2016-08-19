#include "stdafx.h"
#include "WallType.h"

using namespace WallTypeSpace;

void CWallViewType::SetTexture(const std::string & texturePath)
{
	m_texture = LoadTexture2DFromBMP(texturePath);
}

void CWallViewType::SetTexture(CTexture2DSharedPtr pTexture)
{
	m_texture = pTexture;
}

CTexture2DSharedPtr CWallViewType::GetTexture() const
{
	return m_texture;
}

void CWallViewType::SetTextureMap(const glm::vec2 & position)
{
	for (size_t index = 0; index < m_textureMap.size(); ++index)
	{
		m_textureMap[index] = STANDART_UV_TEXTURE_MAP[index] * ( position + glm::vec2(1.f));
	}
}

WallTextureMap CWallViewType::GetTextureMap() const
{
	return m_textureMap;
}

void CWallViewType::SetPositionTile(const glm::vec2 & position)
{
	m_positionTile = position;
	SetTextureMap(position);
}

glm::vec2 CWallViewType::GetPositionTile() const
{
	return m_positionTile;
}

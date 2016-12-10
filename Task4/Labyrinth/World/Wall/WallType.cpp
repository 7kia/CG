#include "stdafx.h"
#include "WallType.h"

using namespace WallTypeSpace;

void CWallViewType::SetTextureMap(const glm::vec2 & position)
{
	for (size_t index = 0; index < m_textureMap.size(); ++index)
	{
		m_textureMap[index].x = STANDART_UV_TEXTURE_MAP[index].x + (position.x / WIDTH_MAP);
		m_textureMap[index].y = STANDART_UV_TEXTURE_MAP[index].y + (position.y / HEIGHT_MAP);

	}
}

CWallViewType::CWallViewType()
	: CHaveTexture()
{
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

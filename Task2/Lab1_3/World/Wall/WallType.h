#pragma once

#include "../../Material/Texture2D.h"

class CWallType
{
public:
	void					SetTexture(const std::string & texturePath);
	CTexture2D*				GetTexture() const;
private:
	CTexture2DUniquePtr		m_texture;
};
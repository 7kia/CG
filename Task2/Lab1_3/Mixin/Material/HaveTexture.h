#pragma once

#include "../../Material/Texture2D.h"

namespace TextureSpace
{
	const std::string PATH_TO_RECOURCES = "Resources/";
	const std::string TexturePaths[] =
	{
		PATH_TO_RECOURCES + "Tiles.bmp",
		PATH_TO_RECOURCES + "Player.bmp",
	};

}

class CHaveTexture
{
public:
	CHaveTexture();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetTexture(const std::string & texturePath);
	void					SetTexture(CTexture2DSharedPtr pTexture);
	CTexture2DSharedPtr		GetTexture() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	CTexture2DSharedPtr		m_texture;

};
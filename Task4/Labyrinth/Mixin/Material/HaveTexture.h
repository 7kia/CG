#pragma once

#include "../../Material/Texture2D.h"
#include <unordered_map>
namespace TextureSpace
{
	const std::string PATH_TO_RECOURCES = "Resources/";

	enum class Id
	{
		Tiles = 0
		, Player
		, Shoot
	};

	static std::unordered_map<size_t, const std::string> TexturePaths =
	{
		{ size_t(Id::Tiles),  PATH_TO_RECOURCES + "Tiles.bmp" },
		{ size_t(Id::Player),  PATH_TO_RECOURCES + "Player.bmp"},
		{ size_t(Id::Shoot),  PATH_TO_RECOURCES + "Shoot.bmp"},
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
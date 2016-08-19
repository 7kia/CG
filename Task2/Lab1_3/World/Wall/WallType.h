#pragma once

#include "../../Material/Texture2D.h"
#include <array>

using WallTextureMap = std::array<glm::vec2, 4>;

// TODO : see need transfer to cpp-file
namespace WallTypeSpace
{
	enum class Id
	{
		Break = 0
		, Plank
		, Arch
		, AmountTypes
	};

	const unsigned AMOUNT_TYPES = unsigned(Id::AmountTypes);
	const unsigned WIDTH_MAP = 2;// In tiles
	const unsigned HEIGHT_MAP = 2;
	const unsigned SIZE_TILE = 750;

	const std::string PATH_TO_RECOURCES = "Resources/";
	const std::string TexturePaths[] =
	{
		PATH_TO_RECOURCES + "Tiles.bmp",
	};

	/*
	// TODO : see need its
	// old
	PATH_TO_RECOURCES + "brick.bmp",
	PATH_TO_RECOURCES + "plank.bmp",
	PATH_TO_RECOURCES + "arch.bmp",

	*/

	const WallTextureMap STANDART_UV_TEXTURE_MAP =
	{
			glm::vec2( 0.f, 0.f )
		,	glm::vec2(1.f / WIDTH_MAP, 0.f )
		,	glm::vec2( 1.f / WIDTH_MAP, 1.f / HEIGHT_MAP )
		,	glm::vec2(0.f, 1.f / HEIGHT_MAP )
	};
};


class CWallViewType
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetTexture(const std::string & texturePath);
	void					SetTexture(CTexture2DSharedPtr pTexture);
	CTexture2DSharedPtr		GetTexture() const; // TODO: return reference

	//  measured in tiles
	WallTextureMap			GetTextureMap() const;

	void					SetPositionTile(const glm::vec2 & position);
	glm::vec2				GetPositionTile() const;

private:
	//  Texture map depent from tile position
	void					SetTextureMap(const glm::vec2 & position);

//////////////////////////////////////////////////////////////////////
// Data
private:
	CTexture2DSharedPtr		m_texture;
	WallTextureMap			m_textureMap = WallTypeSpace::STANDART_UV_TEXTURE_MAP;
	glm::vec2				m_positionTile;// need set int value, measured in tiles
	
};

// TODO : might need transfer
class IHavePointerToWallViewType
{
public:
	virtual ~IHavePointerToWallViewType() = default;

	virtual void						SetType(const CWallViewType* type) = 0;
	virtual const CWallViewType*		GetType() const = 0;
};
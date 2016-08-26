#pragma once

#include "../../Mixin/Material/HaveTexture.h"
#include <array>

using WallTextureMap = std::array<glm::vec2, 4>;

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


	const WallTextureMap STANDART_UV_TEXTURE_MAP =
	{
			glm::vec2( 1.f / WIDTH_MAP, 1.f / HEIGHT_MAP )
		,	glm::vec2(0.f, 1.f / HEIGHT_MAP )
		,	glm::vec2( 0.f, 0.f )
		,	glm::vec2(1.f / WIDTH_MAP, 0.f )
	};
};


class CWallViewType
	: public CHaveTexture
{
public:
	CWallViewType();
//////////////////////////////////////////////////////////////////////
// Methods
public:

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
	WallTextureMap			m_textureMap = WallTypeSpace::STANDART_UV_TEXTURE_MAP;
	glm::vec2				m_positionTile;// need set int value, measured in tiles
	
};

class IHavePointerToWallViewType
{
public:
	virtual ~IHavePointerToWallViewType() = default;

	virtual void						SetType(const CWallViewType* type) = 0;
	virtual const CWallViewType*		GetType() const = 0;
};
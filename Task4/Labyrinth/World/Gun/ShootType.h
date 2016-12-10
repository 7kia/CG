#pragma once

#include "Mixin/Material/HaveTexture.h"
#include <array>


namespace ShootTypeSpace
{
	enum class Id
	{
		Player = 0
		, Enemy
		, AmountTypes
	};


	const unsigned AMOUNT_TYPES = unsigned(Id::AmountTypes);


};

class CShootType
	: public CHaveTexture
{
public:
	CShootType();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// TODO : see need it all
	//  measured in tiles
	//ShootTextureMap			GetTextureMap() const;

	//void					SetPositionTile(const glm::vec2 & position);
	//glm::vec2				GetPositionTile() const;

private:
	//  Texture map depent from tile position
	//void					SetTextureMap(const glm::vec2 & position);

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	// TODO : see need it
	//glm::vec2				m_positionTile;// need set int value, measured in tiles

};
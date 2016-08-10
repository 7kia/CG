#pragma once

#include "Wall.h"
#include <string>

static const std::string PATH_TO_RECOURCES = "Resources/";

static const std::string TexturePathWallTypes[] =
{
	PATH_TO_RECOURCES + "brick.bmp",
	PATH_TO_RECOURCES + "plank.bmp",
};

class CHaveWallTypes
{
public:
	CHaveWallTypes();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	enum class IdWallType
	{
			Break = 0
		,	Plank
		,	AmountTypes
	};

	using ArrayWallTypes = std::array<CWallType, size_t(IdWallType::AmountTypes)>;

	void							CreateWallTypes();// TODO : do call_once
	const CWallType*				GetWallType(unsigned index) const;
private:
	void							SetWallType(unsigned index);
//////////////////////////////////////////////////////////////////////
// Data

protected:
	ArrayWallTypes					m_wallTypes;
};
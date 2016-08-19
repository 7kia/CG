#pragma once

#include "Wall.h"
#include <string>


class CHaveWallTypes
{
public:
	CHaveWallTypes();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	using ArrayWallTypes = std::array<CWallViewType, size_t(WallTypeSpace::AMOUNT_TYPES)>;

	void							CreateWallTypes();// TODO : do call_once
	const CWallViewType*			GetWallType(unsigned index) const;
private:
	void							SetWallType(unsigned index, const glm::vec2 & position);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	ArrayWallTypes					m_wallTypes;
};
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
	const CWallViewType*			GetWallType(size_t index) const;
private:
	void							SetWallType(size_t index, const glm::vec2 & position);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	ArrayWallTypes					m_wallTypes;
};
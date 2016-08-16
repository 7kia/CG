#include "stdafx.h"
#include "../../stdafx.h"
#include "HaveWallTypes.h"

CHaveWallTypes::CHaveWallTypes()
{
}

void CHaveWallTypes::CreateWallTypes()
{
	// TODO: use static_assert from C++11
	if ( (sizeof(TexturePathWallTypes) / sizeof(std::string)) != unsigned(IdWallType::AmountTypes))
	{
		throw std::runtime_error("Amount texture paths incorrect");
	}

	for (unsigned index = unsigned(IdWallType::Break); index < unsigned(IdWallType::AmountTypes); ++index)
	{
		SetWallType(index);
	}
}

const CWallViewType * CHaveWallTypes::GetWallType(unsigned index) const
{
	return &m_wallTypes[index];
}

void CHaveWallTypes::SetWallType(unsigned index)
{
	m_wallTypes[index].SetTexture(TexturePathWallTypes[index]);
}

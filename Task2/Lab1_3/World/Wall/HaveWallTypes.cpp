#include "stdafx.h"
#include "HaveWallTypes.h"

using namespace WallTypeSpace;

CHaveWallTypes::CHaveWallTypes()
{
}

void CHaveWallTypes::CreateWallTypes()
{
	// TODO : see need it
	//static_assert((sizeof(TexturePaths) / sizeof(std::string)) == AMOUNT_TYPES, "Amount texture paths incorrect");

	// 
	//for (unsigned index = unsigned(Id::Break); index < unsigned(Id::AmountTypes); ++index)
	//{
	//	SetWallType(index);
	//}
	SetWallType(unsigned(Id::Break), glm::vec2(1, 1));
	SetWallType(unsigned(Id::Plank), glm::vec2(0, 1));
	SetWallType(unsigned(Id::Arch), glm::vec2(0, 0));


	m_wallTypes[0].SetTexture(TexturePaths[0]);

	for (unsigned index = unsigned(Id::Plank); index < unsigned(Id::AmountTypes); ++index) 
	{
		m_wallTypes[index].SetTexture(m_wallTypes[0].GetTexture());// TODO : see can replace "0"
	}
}

const CWallViewType * CHaveWallTypes::GetWallType(unsigned index) const
{
	return &m_wallTypes[index];
}

void CHaveWallTypes::SetWallType(unsigned index
								, const glm::vec2 & position)
{
	m_wallTypes[index].SetPositionTile(position);
}

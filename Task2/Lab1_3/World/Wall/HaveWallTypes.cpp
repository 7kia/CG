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
	//for (size_t index = size_t(Id::Break); index < size_t(Id::AmountTypes); ++index)
	//{
	//	SetWallType(index);
	//}
	SetWallType(size_t(Id::Break), glm::vec2(1, 1));
	SetWallType(size_t(Id::Plank), glm::vec2(0, 1));
	SetWallType(size_t(Id::Arch), glm::vec2(0, 0));


	m_wallTypes[0].SetTexture(TextureSpace::TexturePaths[0]);

	for (size_t index = size_t(Id::Plank); index < size_t(Id::AmountTypes); ++index) 
	{
		m_wallTypes[index].SetTexture(m_wallTypes[0].GetTexture());// TODO : see can replace "0"
	}
}

const CWallViewType * CHaveWallTypes::GetWallType(size_t index) const
{
	return &m_wallTypes[index];
}

void CHaveWallTypes::SetWallType(size_t index
								, const glm::vec2 & position)
{
	m_wallTypes[index].SetPositionTile(position);
}

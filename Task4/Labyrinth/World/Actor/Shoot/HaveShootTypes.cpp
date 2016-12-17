#include "stdafx.h"
#include "HaveShootTypes.h"
#include "World\World.h"

static std::once_flag shootTypesIsCreate;


CHaveShootTypes::CHaveShootTypes()
{
	SetShootType(CShootType::Id::Player
		, IdFaction::Player
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Shoot)]
		, 2.f);
	SetShootType(CShootType::Id::Enemy
		, IdFaction::Enemy
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Shoot)]
		, 2.f);

}

const CShootType & CHaveShootTypes::GetShootType(const CShootType::Id index) const
{
	return m_shootTypes[size_t(index)];
}

void CHaveShootTypes::SetShootType(CShootType::Id typeIndex
								, IdFaction idFaction
								, const std::string & texturePath
								, int health)
{
	size_t index = size_t(typeIndex);
	m_shootTypes[index].SetId(typeIndex);
	m_shootTypes[index].SetIdFaction(idFaction);

	m_shootTypes[index].SetHealth(health);
	m_shootTypes[index].SetTexture(texturePath);
}



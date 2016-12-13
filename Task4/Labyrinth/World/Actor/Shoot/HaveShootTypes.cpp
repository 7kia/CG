#include "stdafx.h"
#include "HaveShootTypes.h"
#include "World\World.h"

using namespace ShootTypeSpace;

static std::once_flag shootTypesIsCreate;


CHaveShootTypes::CHaveShootTypes()
{
	SetShootType(size_t(Id::Player)
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Shoot)]
		, 2.f);
	SetShootType(size_t(Id::Enemy)
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Shoot)]
		, 2.f);

}

const CShootType & CHaveShootTypes::GetShootType(const ShootTypeSpace::Id index) const
{
	return m_shootTypes[size_t(index)];
}

void CHaveShootTypes::SetShootType(size_t index
								, const std::string & texturePath
								, int health)
{
	m_shootTypes[index].SetHealth(health);
	m_shootTypes[index].SetTexture(texturePath);
}



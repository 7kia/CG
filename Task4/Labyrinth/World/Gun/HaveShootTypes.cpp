#include "stdafx.h"
#include "HaveShootTypes.h"
#include "World\World.h"

using namespace ShootTypeSpace;

std::once_flag shootTypesIsCreate;


CHaveShootTypes::CHaveShootTypes()
{
}

void CHaveShootTypes::CreateShootTypes()
{
	std::call_once(shootTypesIsCreate,
		[&]() {
		SetShootType(size_t(Id::Player));
		SetShootType(size_t(Id::Enemy));


		m_shootTypes[0].SetTexture(TextureSpace::TexturePaths[size_t(TextureSpace::Id::Shoot)]);

		for (size_t index = size_t(Id::Player); index < size_t(Id::AmountTypes); ++index)
		{
			m_shootTypes[index].SetTexture(m_shootTypes[0].GetTexture());// TODO : see can replace "0"
		}

	});
}

const CShootType * CHaveShootTypes::GetShootType(const ShootTypeSpace::Id index) const
{
	return &m_shootTypes[size_t(index)];
}

void CHaveShootTypes::SetShootType(size_t index)
{
	// TODO : rewrite if need
	//m_shootTypes[index].SetPositionTile(position);
}


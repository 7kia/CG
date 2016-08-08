#include "stdafx.h"
#include "Wall.h"

CWall::CWall()
	: ÑCompositeShape()
{
	m_visible.fill(true);

	{
		//IBodyUniquePtr pRectangle = std::make_unique<CRectangle>();
	}

	if (m_visible.size() != m_shapes.size())
	{
		throw std::runtime_error("Amount shapes not equal 6");
	}
}

void CWall::Update(float deltaTime)
{
	(void)deltaTime;
}

void CWall::Draw() const
{
	for (uint index = 0; index < m_visible.size(); ++index)
	{
		if (m_visible[index])
		{
			m_shapes[index]->Draw();
		}
	}
}

void CWall::SetVisible(uint index, bool value)
{
	CheckVisibleIndex(index);

	m_visible[index] = value;
}

bool CWall::GetVisible(uint index) const
{
	CheckVisibleIndex(index);

	return m_visible[index];
}

void CWall::CheckVisibleIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_visible.size())))
	{
		throw std::runtime_error("Wall have not the index");
	}
}

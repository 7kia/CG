#include "stdafx.h"
#include "Wall.h"

CWall::CWall()
	: ŃCompositeShape()
{
	m_visible.fill(true);

	for(uint index = 0; index < 6; ++index)
	{
		IBodyUniquePtr pRectangle = std::make_unique<CRectangle>();
		m_shapes.push_back(std::move(pRectangle));
	}


	for (uint index = 0; index < m_shapes.size(); ++index)
	{
		CRectangle* pRectangle = dynamic_cast<CRectangle*>(m_shapes[index].get());

		const WallSpace::SRectangleFace face = WallSpace::CUBE_FACES[index];

		pRectangle->SetVertexPosition(0, WallSpace::CUBE_VERTICIES[face.vertexIndex1]);
		pRectangle->SetVertexPosition(1, WallSpace::CUBE_VERTICIES[face.vertexIndex2]);
		pRectangle->SetVertexPosition(2, WallSpace::CUBE_VERTICIES[face.vertexIndex3]);
		pRectangle->SetVertexPosition(3, WallSpace::CUBE_VERTICIES[face.vertexIndex4]);
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

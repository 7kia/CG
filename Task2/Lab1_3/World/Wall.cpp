#include "stdafx.h"
#include "Wall.h"

namespace WallSpace
{
	enum class CubeFace
	{
		Front = 0,
		Back,
		Top,
		Bottom,
		Left,
		Right,

		NumFaces
	};

	struct SRectangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t vertexIndex4;
		uint16_t colorIndex;
	};


	const SRectangleFace CUBE_FACES[] = {
		{ 0, 1, 2, 3, static_cast<uint16_t>(CubeFace::Back) },//
		{ 1, 5, 6, 2, static_cast<uint16_t>(CubeFace::Right) },
		{ 3, 2, 6, 7, static_cast<uint16_t>(CubeFace::Bottom) },
		{ 4, 0, 3, 7, static_cast<uint16_t>(CubeFace::Left) },
		{ 1, 0, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
		{ 5, 4, 7, 6, static_cast<uint16_t>(CubeFace::Front) },//
	};

	// Вершины куба служат материалом для формирования треугольников,
	// составляющих грани куба.
	const Vertex CUBE_VERTICIES[] = {
		{ -1, +1, -1 },
		{ +1, +1, -1 },
		{ +1, -1, -1 },
		{ -1, -1, -1 },
		{ -1, +1, +1 },
		{ +1, +1, +1 },
		{ +1, -1, +1 },
		{ -1, -1, +1 },
	};
}


CWall::CWall()
	: СCompositeShape()
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

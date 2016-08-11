#include "stdafx.h"
#include "WallView.h"

CWallView::CWallView()
	: ÑComposite3DShape()
{
	m_visible.fill(true);

	for(uint index = 0; index < 6; ++index)
	{
		IBodyUniquePtr pRectangle = std::make_unique<C3DRectangle>();
		m_shapes.push_back(std::move(pRectangle));
	}


	for (uint index = 0; index < m_shapes.size(); ++index)
	{
		C3DRectangle* pRectangle = dynamic_cast<C3DRectangle*>(m_shapes[index].get());

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

void CWallView::Draw() const
{
	for (uint index = 0; index < m_visible.size(); ++index)
	{
		if (m_visible[index])
		{
			GetTexture()->DoWhileBinded([&] {
				m_shapes[index]->Draw();
			});
		}
	}
}

void CWallView::SetType(const CWallViewType* type)
{
	m_pType = type;
}

const CWallViewType* CWallView::GetType() const
{
	return m_pType;
}

void CWallView::SetVisible(uint index, bool value)
{
	CheckVisibleIndex(index);

	m_visible[index] = value;
}

bool CWallView::GetVisible(uint index) const
{
	CheckVisibleIndex(index);

	return m_visible[index];
}

void CWallView::CheckVisibleIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_visible.size())))
	{
		throw std::runtime_error("Wall have not the index");
	}
}

CTexture2D * CWallView::GetTexture() const
{
	return m_pType->GetTexture();
}

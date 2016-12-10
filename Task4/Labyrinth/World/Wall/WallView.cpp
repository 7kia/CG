#include "stdafx.h"
#include "WallView.h"

CWallView::CWallView()
	: ÑComposite3DShape()
	, CHaveVisiblePart(6)
{
	for(size_t index = 0; index < 6; ++index)
	{
		IBodySharedPtr pRectangle = std::make_unique<C3DRectangle>();
		m_shapes.push_back(std::move(pRectangle));
	}

	for (size_t index = 0; index < m_shapes.size(); ++index)
	{
		C3DRectangle* pRectangle = dynamic_cast<C3DRectangle*>(m_shapes[index].get());

		const WallSpace::SRectangleFace face = WallSpace::CUBE_FACES[index];

		pRectangle->SetSourceVertexPosition(0, WallSpace::CUBE_VERTICIES[face.vertexIndex1]);
		pRectangle->SetSourceVertexPosition(1, WallSpace::CUBE_VERTICIES[face.vertexIndex2]);
		pRectangle->SetSourceVertexPosition(2, WallSpace::CUBE_VERTICIES[face.vertexIndex3]);
		pRectangle->SetSourceVertexPosition(3, WallSpace::CUBE_VERTICIES[face.vertexIndex4]);

		pRectangle->UpdateNormals();
	}

	if (m_visible.size() != m_shapes.size())
	{
		throw std::runtime_error("Amount shapes not equal 6");
	}
}

void CWallView::Draw() const
{
	GetTexture()->DoWhileBinded([&] {
		for (size_t index = 0; index < m_visible.size(); ++index)
		{
			if (m_visible[index])
			{
				m_shapes[index]->Draw();
			}
		}
	});

}

void CWallView::SetType(const CWallViewType* type)
{
	m_pType = type;

	for (auto & shape : m_shapes)
	{
		auto rectangle = dynamic_cast<C3DRectangle*>(shape.get());

		const auto & textureMap = GetType()->GetTextureMap();
		for (size_t indexVertex = 0; indexVertex < textureMap.size(); ++indexVertex)
		{
			rectangle->SetVertexTexCoordinate(indexVertex, textureMap[indexVertex]);
		}
	}
}

const CWallViewType* CWallView::GetType() const
{
	return m_pType;
}

void CWallView::SetTransform(const glm::mat4 & transform)
{
	CTransformable::SetTransform(transform);
	for (auto & shape : m_shapes)
	{
		shape->SetTransform(transform);
	}
}

CTexture2DSharedPtr CWallView::GetTexture() const
{
	return m_pType->GetTexture();
}

#include "stdafx.h"
#include "ShootView.h"

CShootView::CShootView()
	: ÑComposite3DShape()
{
	// Might need several shapes
	IBodySharedPtr pSphere = std::make_unique<CIdentity3DSphere>(16, 16);
	m_shapes.push_back(std::move(pSphere));
	
}

void CShootView::Draw() const
{
	GetTexture()->DoWhileBinded([&] {
		for (auto & shape : m_shapes)
		{
			shape->Draw();
		}
	});
}

void CShootView::SetType(const CShootType* type)
{
	m_pType = type;
}

const CShootType* CShootView::GetType() const
{
	return m_pType;
}

void CShootView::SetTransform(const glm::mat4 & transform)
{
	CTransformable::SetTransform(transform);
	for (auto & shape : m_shapes)
	{
		shape->SetTransform(transform);
	}
}

CTexture2DSharedPtr CShootView::GetTexture() const
{
	return m_pType->GetTexture();
}


#include "stdafx.h"
#include "ShootView.h"

CShootView::CShootView()
	: ÑComposite3DShape()
{
	// Might need several shapes
	IBodySharedPtr pSphere = std::make_unique<CIdentity3DSphere>(16, 16);
	pSphere->SetRadiuse(0.25f);
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

void CShootView::SetRadius(float value)// TODO : see need it
{
	glm::mat4 transform = m_shapes[0]->GetTransform();

	//auto collisionPosition = m_collision.GetPosition();
	auto position = glm::vec3(transform[0][3], 0.f, transform[2][3]);

	transform = glm::translate(glm::mat4(), position);
	transform *= glm::scale(glm::mat4(), glm::vec3(value));// TODO : fix

	m_shapes[0]->SetTransform(transform);
}


CTexture2DSharedPtr CShootView::GetTexture() const
{
	return m_pType->GetTexture();
}


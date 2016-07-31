#include "stdafx.h"
#include "AbstractShapeDecorator.h"


CAbstractShapeDecorator::CAbstractShapeDecorator()
	: IShape()
{
}

void CAbstractShapeDecorator::SetChild(IBodyUniquePtr &&pChild)
{
	m_pChild = std::move(pChild);
}

void CAbstractShapeDecorator::Update(float deltaTime)
{
	assert(m_pChild.get());
	m_pChild->Update(deltaTime);
}

void CAbstractShapeDecorator::Draw() const
{
	assert(m_pChild.get());
	m_pChild->Draw();
}

void CAbstractShapeDecorator::SetFaceColor(const glm::vec4 & color)
{
	m_pChild->SetFaceColor(color);
}

glm::vec4 CAbstractShapeDecorator::GetFaceColor() const
{
	return m_pChild->GetFaceColor();
}

void CAbstractShapeDecorator::SetAlpha(float alpha)
{
	m_pChild->SetAlpha(alpha);
}

float CAbstractShapeDecorator::GetAlpha() const
{
	return m_pChild->GetAlpha();
}

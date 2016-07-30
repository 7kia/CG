#include "stdafx.h"
#include "AbstractShapeDecorator.h"


void CAbstractShapeDecorator::SetChild(IBodyUniquePtr &&pChild)
{
	m_pChild = std::move(pChild);
}

void CAbstractShapeDecorator::UpdateChild(float deltaTime)
{
	assert(m_pChild.get());
	m_pChild->Update(deltaTime);
}

void CAbstractShapeDecorator::DrawChild() const
{
	assert(m_pChild.get());
	m_pChild->Draw();
}

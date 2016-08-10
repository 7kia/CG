#include "stdafx.h"
#include "AbstractShapeDecorator.h"


CAbstractShapeDecorator::CAbstractShapeDecorator()
	: I3DShape()
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
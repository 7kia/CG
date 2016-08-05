#include "stdafx.h"
#include "Texture2DShapeDecorator.h"

CTexture2DShapeDecorator::CTexture2DShapeDecorator()
	: CAbstractShapeDecorator()
{
}

CTexture2DShapeDecorator::CTexture2DShapeDecorator(const std::string & texturePath, unsigned int index)
	: CAbstractShapeDecorator()
	, m_pTexture(LoadTexture2DFromBMP(texturePath))
{
	m_pTexture->SetIndex(index);
}

void CTexture2DShapeDecorator::Update(float deltaTime)
{
	m_pChild->Update(deltaTime);
}

void CTexture2DShapeDecorator::Draw() const
{
	m_pTexture->DoWhileBinded([&] {
		m_pChild->Draw();
	});
}

void CTexture2DShapeDecorator::SetTexture(const std::string & texturePath, unsigned int index)
{
	m_pTexture = LoadTexture2DFromBMP(texturePath);
	m_pTexture->SetIndex(index);
}

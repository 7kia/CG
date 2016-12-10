#include "stdafx.h"
#include "HaveTexture.h"

CHaveTexture::CHaveTexture()
{
}

void CHaveTexture::SetTexture(const std::string & texturePath)
{
	m_texture = LoadTexture2DFromBMP(texturePath);
}

void CHaveTexture::SetTexture(CTexture2DSharedPtr pTexture)
{
	m_texture = pTexture;
}

CTexture2DSharedPtr CHaveTexture::GetTexture() const
{
	return m_texture;
}

#pragma once

#include "AbstractShapeDecorator.h"
#include "../Material/Texture2D.h"
#include <glm/mat3x3.hpp>

class CTexture2DShapeDecorator : public CAbstractShapeDecorator
{
public:
	CTexture2DShapeDecorator();
	CTexture2DShapeDecorator(const std::string & texturePath, unsigned int index);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void Update(float deltaTime) override;
	void Draw() const override;
	//--------------------------------------------

	void SetTexture(const std::string & texturePath, unsigned int index);
//////////////////////////////////////////////////////////////////////
// Data
private:
	CTexture2DUniquePtr m_pTexture;
};
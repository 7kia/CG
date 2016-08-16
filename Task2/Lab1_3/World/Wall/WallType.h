#pragma once

#include "../../Material/Texture2D.h"

class CWallViewType
{
public:
	void					SetTexture(const std::string & texturePath);
	CTexture2D*				GetTexture() const; // TODO: return reference
private:
	CTexture2DUniquePtr		m_texture;
};

// TODO : might need transfer
class IHavePointerToWallViewType
{
public:
	virtual ~IHavePointerToWallViewType() = default;

	virtual void						SetType(const CWallViewType* type) = 0;
	virtual const CWallViewType*		GetType() const = 0;
};
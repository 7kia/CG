#pragma once

#include "3DShape/3DRectangle.h"
#include "Mixin/HaveVisiblePart.h"
#include <array>
#include "ShootType.h"


class CShootView final
	: public ÑComposite3DShape
{
public:
	CShootView();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// CIdentity3DShape
	void						Draw() const override final;
	//--------------------------------------------
	void						SetType(const CShootViewType* type);
	const CShootViewType*		GetType() const;
	//--------------------------------------------
	// ITransformable
	void						SetTransform(const glm::mat4 & transform) override;
	//--------------------------------------------
private:
	CTexture2DSharedPtr			GetTexture() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	const CShootViewType*		m_pType = nullptr; // TODO: nullptrize me
};

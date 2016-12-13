#pragma once

#include "3DShape/3DSphere.h"
#include "3DShape/Composite3DShape.h"
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
	void						SetType(const CShootType* type);
	const CShootType*			GetType() const;
	//--------------------------------------------
	// ITransformable
	void						SetTransform(const glm::mat4 & transform) override;
	//--------------------------------------------

	void						SetRadius(float value);
private:
	CTexture2DSharedPtr			GetTexture() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	const CShootType*			m_pType = nullptr; // TODO: nullptrize me
};

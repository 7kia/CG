#pragma once

#include "..\Mixin\Material\HaveAmbient.h"
#include "..\Mixin\Material\HaveDiffuse.h"
#include "..\Mixin\Material\HaveSpecular.h"
#include "..\Mixin\Material\HaveEmission.h"
#include "..\Mixin\Material\HaveShininess.h"


class CPhongModelMaterial
	: public CHaveEmission
	, public CHaveAmbient
	, public CHaveDiffuse
	, public CHaveSpecular
	, public CHaveShininess
{
public:
	CPhongModelMaterial();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void Setup() const;
};

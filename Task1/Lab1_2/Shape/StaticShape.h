#pragma once

#include "CShape.h"

#include <stdexcept>

namespace NONE_VALUE
{
	const float FLOAT = std::numeric_limits<float>::min();
	const glm::vec2 GLM_VEC2 = glm::vec2(FLOAT, FLOAT);
}

class IStaticShape
{
public:
	virtual ~IStaticShape() = default;


//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				Advance(float dt) = 0;// TODO : see need this

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	virtual void				CheckParametres() {};
	virtual void				SetVisual() {};
};

class CStaticShape
	: public IStaticShape
	, public CDrawable// need only for draw
	, public CHaveOrigin
	, public CHavePosition
	, public IAdvancable
{
public:
	CStaticShape();
	virtual ~CStaticShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
//////////////////////////////////////////////////////////////////////
// Methods
protected:
	//--------------------------------------------
	// IStaticShape
	void						CheckParametres() override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
public:

	//b2Body*						m_body = nullptr;
	//b2BodyDef					m_defBody;
};
#pragma once

#include "CShape.h"
#include <Box2D\Box2d.h>

#include <stdexcept>

namespace NONE_VALUE
{
	const float FLOAT = std::numeric_limits<float>::min();
	const glm::vec2 GLM_VEC2 = glm::vec2(FLOAT, FLOAT);
}

class IStaticShape
	: public CHaveOrigin
	, public IHavePosition
	, public IRotatable
{
public:
	virtual ~IStaticShape() = default;


//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				AddToWorld(b2World * world) = 0;
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
{
public:
	CStaticShape();
	virtual ~CStaticShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//--------------------------------------------
	// IHavePosition
	void						SetPosition(const glm::vec2 & position) override;
	void						SetPosition(float x, float y) override;
	glm::vec2					GetPosition() const override;

	glm::vec2					GetCenterPosition(const glm::vec2 & origin) const override;
	glm::vec2					GetCenterPosition() const override;
	//--------------------------------------------
	// IRotatable
	float						GetRotation() const override;
	void						SetRotation(float rotation) override;
	//--------------------------------------------
	// IStaticShape
	void						AddToWorld(b2World * world) override;
	void						Advance(float dt) override { (void)dt;  };
	//--------------------------------------------
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
	b2Body*						m_body = nullptr;
	b2BodyDef					m_defBody;
};
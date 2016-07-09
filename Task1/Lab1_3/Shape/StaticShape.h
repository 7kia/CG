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
{
public:
	virtual ~IStaticShape() = default;


//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				AddToWorld(b2World * world) = 0;
	virtual void				Advance(float dt) = 0;

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	virtual void				CreateBody() {};
	virtual void				CheckParametres() {};
};

class CStaticShape
	: public IStaticShape
	, public CShape
{
public:
	CStaticShape(b2World * world);
	virtual ~CStaticShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//--------------------------------------------
	// IShape
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

	void						AddToWorld(b2World * world) override;
	void						Advance(float dt) override { (void)dt;  };
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
	b2Body*						m_body;
	b2BodyDef					m_defBody;

};
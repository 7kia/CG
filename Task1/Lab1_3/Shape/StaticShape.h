#pragma once

#include "CShape.h"
#include <Box2D\Box2d.h>

static const float SCALE = 30.f;

float ConvertToBoxCoordinates(const float value);
glm::vec2 ConvertToBoxCoordinates(const glm::vec2 & value);

float ConvertToNormalCoordinates(const float value);
glm::vec2 ConvertToNormalCoordinates(const glm::vec2 & value);

class IStaticShape
{
public:
	virtual ~IStaticShape() = default;


//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				AddInWorld(b2World * world) = 0;
	virtual void				Advance(float dt) = 0;

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	virtual void				CreateBody() = 0;

};

class CStaticShape
	: public IStaticShape
	, public CShape
{
public:
	CStaticShape();
	virtual ~CStaticShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void						AddInWorld(b2World * world) override { (void)world; };
	void						Advance(float dt) override { (void)dt;  };
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void						CreateBody() override {};
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::shared_ptr<b2Body>		m_body;
	b2BodyDef					m_defBody;

};
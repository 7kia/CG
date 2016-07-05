#pragma once

#include "CShape.h"
#include <Box2D\Box2d.h>

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

	void						AddInWorld(b2World * world) override { (void)world; };
	void						Advance(float dt) override { (void)dt;  };
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void						CreateBody() override {};
//////////////////////////////////////////////////////////////////////
// Data
public:
	b2Body*						m_body;
	b2BodyDef					m_defBody;

};
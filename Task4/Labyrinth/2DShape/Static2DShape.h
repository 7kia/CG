#pragma once

#include "2DShape.h"
#include <Box2D\Box2d.h>

#include <boost/noncopyable.hpp>
#include <stdexcept>

namespace NONE_VALUE
{
	const float FLOAT = std::numeric_limits<float>::min();
	const glm::vec2 GLM_VEC2 = glm::vec2(FLOAT, FLOAT);
}

class IStatic2DShape
	: public IHave2DPosition
	, public I2DRotatable
{
public:
	virtual ~IStatic2DShape() = default;


//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				AddToWorld(b2World * world) = 0;
	virtual void				Advance(float dt) = 0;

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	virtual void				CheckParametres() {};
};

class IActor;

class CStatic2DShape
	: public IStatic2DShape
	, public CHave2DOrigin
{
public:
	CStatic2DShape();
	virtual ~CStatic2DShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//--------------------------------------------
	// IHave3DPosition
	void						SetPosition(const glm::vec2 & position) override;
	void						SetPosition(float x, float y) override;
	glm::vec2					GetPosition() const override;

	glm::vec2					GetCenterPosition(const glm::vec2 & origin) const;
	glm::vec2					GetCenterPosition() const;
	//--------------------------------------------
	// I2DRotatable
	float						GetRotation() const override;
	void						SetRotation(float rotation) override;
	//--------------------------------------------
	// IStatic2DShape
	void						AddToWorld(b2World * world) override;
	void						Advance(float dt) override { (void)dt;  };
	//--------------------------------------------

	void						SetMaster(IActor * master);
	IActor*						GetMaster();
//////////////////////////////////////////////////////////////////////
// Methods
protected:
	//--------------------------------------------
	// IStatic2DShape
	void						CheckParametres() override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
public:
	b2Body*						m_body = nullptr;
	b2BodyDef					m_defBody;
};
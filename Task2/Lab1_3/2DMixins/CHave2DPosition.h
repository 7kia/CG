#pragma once

#include <glm/vec2.hpp>

static const float SCALE = 30.f;

namespace Convert
{
	float ToBox(const float value);
	glm::vec2 ToBox(const glm::vec2 & value);

	float ToNormal(const float value);
	glm::vec2 ToNormal(const glm::vec2 & value);
}

//
// Coordinates accept in world coordinate system and convert to Box2d system
//
class IHave2DPosition
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual ~IHave2DPosition() = default;

	virtual void				SetPosition(const glm::vec2 & position) = 0;
	virtual void				SetPosition(float x, float y) = 0;
	virtual glm::vec2			GetPosition() const = 0;
//////////////////////////////////////////////////////////////////////
};

class CHave2DPosition
	: public IHave2DPosition
{
public:
	CHave2DPosition();
	virtual ~CHave2DPosition() = default;

//////////////////////////////////////////////////////////////////////
// Methods
public:

	void				SetPosition(const glm::vec2 & position) override;
	void				SetPosition(float x, float y) override;
	glm::vec2			GetPosition() const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2			m_position;
};
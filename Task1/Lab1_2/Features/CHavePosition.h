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

class IHavePosition
{
public:
	virtual ~IHavePosition() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				SetPosition(const glm::vec2 & position) { (void)position;  };
	virtual void				SetPosition(float x, float y) { (void)x; (void)y; };
	virtual glm::vec2			GetPosition() const { return glm::vec2(); };
//////////////////////////////////////////////////////////////////////
};

class CHavePosition
	: public IHavePosition
{
public:
	CHavePosition();
	virtual ~CHavePosition() = default;
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
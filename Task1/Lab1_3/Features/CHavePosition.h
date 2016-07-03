#pragma once

#include <glm/vec2.hpp>

class IHavePosition
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual ~IHavePosition() = default;

	virtual void				SetPosition(const glm::vec2 & position) = 0;
	virtual void				SetPosition(float x, float y) = 0;
	virtual glm::vec2			GetPosition() const = 0;

	virtual glm::vec2			GetCenterPosition(const glm::vec2 & origin) const = 0;
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

	void				SetPosition(const glm::vec2 & position);
	void				SetPosition(float x, float y);
	glm::vec2			GetPosition() const;

	glm::vec2			GetCenterPosition(const glm::vec2 & origin) const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2			m_position;
//////////////////////////////////////////////////////////////////////
};
#pragma once

#include <glm/vec2.hpp>

class CHavePosition
{
public:
	virtual ~CHavePosition() = default;
public:

	void				SetPosition(const glm::vec2 & position);
	void				SetPosition(float x, float y);
	glm::vec2			GetPosition() const;

protected:// see might need protected
	glm::vec2			m_position;
};
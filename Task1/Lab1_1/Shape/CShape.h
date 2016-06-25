#pragma once

#include "IShape.h"

namespace Colors
{
	const glm::vec3 LIGHT_YELLOW = { 1.f, 1.f, 0.5f };
	const glm::vec3 RED = { 1, 0, 0 };
	const glm::vec3 ORANGE = { 1.f, 0.5f, 0.f };
	const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
	const glm::vec4 QUIET_GREEN = { 0.f, 0.5f, 0.2f, 1.f };
	const glm::vec3 BLACK = { 0.f, 0.f, 0.f };
}

//////////////////////////////////////////
// CShape - basic for everything shapes, consist common data
//////////////////////////////////////////
class CShape
	: public IShape
	, public CDrawable
{
public:
	CShape() = default;
	virtual ~CShape();

public:// Methods
	void					SetOutlineColor(const glm::vec3 &color);
	glm::vec3				GetOutlineColor() const override;
public:// Data

protected:// Methods

protected:// Data
	glm::vec3				m_outlineColor;

};
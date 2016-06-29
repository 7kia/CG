#pragma once

#include "IShape.h"
#include "CHavePosition.h"

namespace Colors
{
	const glm::vec3 LIGHT_YELLOW = { 1.f, 1.f, 0.5f };
	const glm::vec3 RED = { 1, 0, 0 };
	const glm::vec3 ORANGE = { 1.f, 0.5f, 0.f };
	const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
	const glm::vec4 QUIET_GREEN = { 0.f, 0.5f, 0.2f, 1.f };
	const glm::vec3 BLACK = { 0.f, 0.f, 0.f };
}

static const float SCALE_FACTOR = 25.f;


struct SIntRect
{
	float x;
	float y;
	float width;
	float height;
};

//////////////////////////////////////////
// CShape - basic for everything shapes, consist common data
//////////////////////////////////////////
class CShape
	: public IShape
	, public CDrawable
	, public CHavePosition
{
public:
	CShape() = default;
	virtual ~CShape() = default;

public:// Methods
	void					SetOutlineColor(const glm::vec3 &color) override;
	glm::vec3				GetOutlineColor() const override;

	void					SetOrigin(const glm::vec2 & origin) override;
	glm::vec2				GetOrigin() const override;

public:// Data

protected:// Methods

protected:// Data
	glm::vec3				m_outlineColor;
	glm::vec2				m_origin;// for transfer graph to center window


};
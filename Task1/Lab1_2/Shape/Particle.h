#pragma once

#include "CShape.h"

static const glm::vec3 INSIDE_COLOR = { 0.f, 0.f, 0.f };
static const glm::vec3 POSITIVE_COLOR = { 1.f, 0.f, 0.f };
static const glm::vec3 NEGATIVE_COLOR = { 0.f, 0.f, 1.f };

static const float WIDTH_SIGN = 5.f;
static const float HEIGHT_SIGN = 25.f;

class CParticle final
	: public CShape
	, private boost::noncopyable

{
public:
	CParticle();
	CParticle(const glm::vec2 &position
			, float radiuse
			, float thiknessOutline
			, bool isNegative = false
			);

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		SetPosition(const glm::vec2 &position);
	glm::vec2	GetPosition() const;

	void		SetRadiuse(float radius);
	float		GetRadiuse() const;

	void		SetOutlineThikness(float thikness);
	float		GetOutlineThikness() const;

	void		SetSign(bool isNegative);
	bool		GetSign() const;
	// Methods
private:
	void		ChangeColor();
	void		StrokeCircle() const;
	void		FillCircle() const;
	// Constants
private:
	static const int AMOUNT_POINTS = 360;
	// Data
private:
	glm::vec2	m_position;
	float		m_radius;

	float		m_thikness;

	bool		m_isNegative = false;
};
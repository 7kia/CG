#pragma once

#include "CShape.h"
#include "Plus.h"// for draw plus and minus

#include <vector>
#include <memory>

static const glm::vec3 INSIDE_COLOR = { 0.f, 0.f, 0.f };

class CParticle final
	: public CShape
	, private boost::noncopyable

{
public:
	CParticle();
	CParticle(const glm::vec2 &position, bool isNegative = false);

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		SetPosition(const glm::vec2 &position);
	glm::vec2	GetPosition() const;

	void		SetSign(bool isNegative);
	bool		GetSign() const;
	// Methods
private:
	void		ChangeColor();
	void		StrokeCircle() const;
	void		FillCircle() const;

	void		DefineCenterSign();
	// Constants
private:
	static const int AMOUNT_POINTS = 360;
	// Data
private:
	std::unique_ptr<CShape>	m_shapeSign;// for draw plus and minus

	glm::vec2	m_position;

	bool		m_isNegative = false;
};
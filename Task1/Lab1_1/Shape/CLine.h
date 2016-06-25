#pragma once

#include "CShape.h"

class CLine final
	: public CShape
	, private boost::noncopyable

{
public:
	CLine();
	CLine(const glm::vec2 &firstPoint
		, const glm::vec2 &secondPoint
		, const glm::vec3 &color
		, float thikness);

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		SetFirstPoint(const glm::vec2 &firstPoint);
	glm::vec2	GetFirstPoint() const;

	void		SetSecondPoint(const glm::vec2 &secondPoint);
	glm::vec2	GetSecondPoint() const;

	void		SetThikness(float thikness);
	float		GetThikness() const;


private:
	glm::vec2	m_firstPoint;
	glm::vec2	m_secondPoint;
	float		m_thikness;
};
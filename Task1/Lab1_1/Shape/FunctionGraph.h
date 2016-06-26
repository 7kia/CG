#pragma once

#include "CShape.h"

class CFunctionGraph final// was exported from third lab by OOP
	: public CShape
	, private boost::noncopyable

{
public:
	CFunctionGraph();
	CFunctionGraph(glm::vec2 origin
					, float start
					, float end
					, const glm::vec3 & outlineColor);
	~CFunctionGraph();

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		SetStart(float start);
	float		GetStart() const;

	void		SetEnd(float end);
	float		GetEnd() const;

// Methods
private:
	float		GetValueFunction(float x) const;

// Constants
private:
	const float	AMOUNT_POINTS = 40.f;
	const float	EPSILON = 1e-4;

// Data
private:
	float		m_start = 0.f;
	float		m_end = 0.f;
};
#pragma once

#include "IFunctionGraph.h"

class CFunctionGraph// was exported from third lab by OOP
	: public IFunctionGraph
{
public:
	CFunctionGraph() = default;
	CFunctionGraph(glm::vec2 origin
					, float start
					, float end
					, const glm::vec3 & outlineColor);
	~CFunctionGraph() = default;

public:
	void		SetStart(float start);
	float		GetStart() const;

	void		SetEnd(float end);
	float		GetEnd() const;

// Constants
protected:
	const float	AMOUNT_POINTS = 40.f;
	const float	EPSILON = 1e-4;

// Data
protected:
	float		m_start = 0.f;
	float		m_end = 0.f;
};
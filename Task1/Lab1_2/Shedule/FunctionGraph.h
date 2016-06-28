#pragma once

#include "IFunctionGraph.h"

static const int	AMOUNT_POINTS = 100;
static const float	EPSILON = static_cast<float>(1e-4);

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

// Data
protected:
	float		m_start = 0.f;
	float		m_end = 0.f;
};
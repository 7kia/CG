#pragma once

#include "FunctionGraph.h"

class CArchimedeanSpiral final// was exported from third lab by OOP
	: public CFunctionGraph
	, private boost::noncopyable

{
public:
	CArchimedeanSpiral();
	CArchimedeanSpiral(glm::vec2 origin
		, float start
		, float end
		, const glm::vec3 & outlineColor);
	~CArchimedeanSpiral() = default;

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	// Methods
private:
	float		GetFunctionValue(float angle) const override;
	float		GetX(float angle) const;

	// Data
private:
	float		m_spiralStep = 1.f;
};
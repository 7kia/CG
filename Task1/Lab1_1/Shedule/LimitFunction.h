#pragma once

#include "FunctionGraph.h"

class CLimitFunction final// was exported from third lab by OOP
	: public CFunctionGraph
	, private boost::noncopyable

{
public:
	CLimitFunction();
	CLimitFunction(glm::vec2 origin
					, float start
					, float end
					, const glm::vec3 & outlineColor);
	~CLimitFunction() = default;

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

// Methods
private:
	float		GetValueFunction(float x) const override;
};
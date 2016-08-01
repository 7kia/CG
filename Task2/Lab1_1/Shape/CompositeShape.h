#pragma once

#include "../Mixin/Drawable.h"
#include "Shape.h"
#include <vector>


class ÑCompositeShape 
	: public CShape
{
public:
	ÑCompositeShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IHaveFaceColor
	void					SetFaceColor(const glm::vec4 &color) override;

	void					SetAlpha(float alpha) override;
	//--------------------------------------------
	// IHaveFaceColor for components
	void					SetFaceColor(size_t index, const glm::vec4 &color);
	glm::vec4				GetFaceColor(size_t index) const;

	void					SetAlpha(size_t index, float alpha);
	float					GetAlpha(size_t index) const;
	//--------------------------------------------
	// IShape
	void					Draw() const override final;
	//--------------------------------------------
private:
	void					CheckIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};
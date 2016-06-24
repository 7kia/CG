#pragma once

#include "IShape.h"

//////////////////////////////////////////
// CShape - basic for everything shapes, consist common data
//////////////////////////////////////////
class CShape
	: public IShape
{
public:
	CShape() = default;
	virtual ~CShape();

public:// Methods
	void					Draw() const override;

	void					SetOutlineColor(const glm::vec3 &color);
	glm::vec3				GetOutlineColor() const override;
public:// Data

protected:// Methods
	void					DeleteList();

protected:// Data
	mutable unsigned		m_displayList = 0;
	glm::vec3				m_outlineColor;

};
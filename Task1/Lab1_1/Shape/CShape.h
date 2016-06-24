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

public:
	void					SetOutlineColor(const glm::vec3 &color);
	void					Draw() const;

private:
	void					DeleteList();

private:
	mutable unsigned		m_displayList = 0;
	glm::vec3				m_outlineColor;

};
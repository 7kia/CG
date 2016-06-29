#pragma once

#include "CShape.h"
#include "CHavePosition.h"

class CRectangle final
	: public CShape
	, private boost::noncopyable

{
public:
	CRectangle();
	CRectangle(const glm::vec2 & leftTopPoint
				, float width
				, float height
				, float rotate
				, const glm::vec3 & outlineColor);
	~CRectangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void				Redraw() const override;
	bool				HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------

	void				SetWidth(float width);
	float				GetWidth() const;

	void				SetHeight(float height);
	float				GetHeight() const;

	void				SetRotate(float angle);
	float				GetRotate() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	float				m_width;
	float				m_height;
	float				m_rotation = 0;
//////////////////////////////////////////////////////////////////////
};
#pragma once

#include "CShape.h"
#include "StaticShape.h"

class CRectangle final
	: public CStaticShape
	, private boost::noncopyable

{
public:
	CRectangle(b2World * world);
	CRectangle(const glm::vec2 & leftTopPoint
				, float width
				, float height
				, float rotate
				, const glm::vec3 & outlineColor
				, b2World * world);
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

	//--------------------------------------------
	// IStaticShape
	void				AddToWorld(b2World * world) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStaticShape
	void				CreateBody() override;
	void				CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	float				m_width = NONE_VALUE::FLOAT;
	float				m_height = NONE_VALUE::FLOAT;
//////////////////////////////////////////////////////////////////////
};
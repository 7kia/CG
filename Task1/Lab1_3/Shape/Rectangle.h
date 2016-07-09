#pragma once

#include "CShape.h"
#include "StaticShape.h"

struct SSize
{
	SSize();
	SSize(float width, float height);
	float width = 0.f;
	float height = 0.f;
};

class CRectangle final
	: public CStaticShape
	, private boost::noncopyable

{
public:
	CRectangle(b2World * world);
	CRectangle(const glm::vec2 & leftTopPoint
				, SSize size
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

	static void			AddRectangleToBody(b2Body *body
											, SSize size
											, float rotatation
											, const glm::vec2 & shapeOrigin);// TODO : see need transfer
	//--------------------------------------------
	// IStaticShape
	void				AddToWorld(b2World * world) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStaticShape
	void				CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	float				m_width = NONE_VALUE::FLOAT;
	float				m_height = NONE_VALUE::FLOAT;
//////////////////////////////////////////////////////////////////////
};
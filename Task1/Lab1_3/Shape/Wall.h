#pragma once

#include "RectangleView.h"

class CWall final
	: public CStaticShape
	, public CDrawable
	, public IShape
	, public CRectangle
	, private boost::noncopyable
{
public:
	CWall(b2World * world);
	CWall(const glm::vec2 & leftTopPoint
		, SSize size
		, float rotate
		, const glm::vec3 & outlineColor
		, b2World * world);
	virtual ~CWall() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void			AddRectangleToBody(b2Body *body
											, SSize size
											, float rotatation
											, const glm::vec2 & shapeOrigin);// TODO : see need transfer
	//--------------------------------------------
	// IStaticShape
	void				AddToWorld(b2World * world) override;
	void				SetVisual() override;
	//--------------------------------------------
	// CDrawable
	void				Redraw() const;
	bool				HitTest(const glm::vec2 &point) const;
	//--------------------------------------------
	// IShape
	void				SetOutlineColor(const glm::vec3 &color) override;
	glm::vec3			GetOutlineColor() const override;
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
	CRectangleView		m_visual;

};
#pragma once

#include "RectangleView.h"

class CWall final
	: public CStaticShape
	, public IShape
	, public CRectangle
	, private boost::noncopyable
{
public:
	CWall();
	CWall(const glm::vec2 & leftTopPoint
		, SSize size
		, float rotate
		, const glm::vec3 & outlineColor
		);
	virtual ~CWall() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void			AddRectangleToBody(b2Body *body
											, SSize size
											, const glm::vec2 & shapeOrigin);// TODO : see need transfer
	//--------------------------------------------
	// IStaticShape
	void				AddToWorld(b2World * world) override;
	// Update visual part
	void				Advance(float dt) override;
	// Set visual part before create body, because view can have
	// different from body
	void				SetVisual() override;
	//--------------------------------------------

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
#pragma once

#include "CircleView.h"

class CBall
	: public CDynamicBody
	, public IShape
	, public CCircle
	, private boost::noncopyable

{
public:
	CBall();
	CBall(float radius, const glm::vec2 &position);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IStaticShape
	// Update visual part
	void			Advance(float dt) override;
	// Set visual part before create body, because view can have
	// different from body
	void			SetVisual() override;
	//--------------------------------------------
	// CDrawable
	void			Redraw() const;
	bool			HitTest(const glm::vec2 &point) const;
	//--------------------------------------------
	// IShape
	void			SetOutlineColor(const glm::vec3 &color) override;
	glm::vec3		GetOutlineColor() const override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStaticShape
	void			CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	CCircleView		m_visual;
};
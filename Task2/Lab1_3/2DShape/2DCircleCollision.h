#pragma once

#include "Dynamic2DShape.h"
#include "Circle.h"

class CBall
	: public CDynamicBody
	, public I2DShape
	, public CCircle
	, private boost::noncopyable

{
public:
	CBall();
	CBall(float radius, const glm::vec2 &position);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void		AddCircleToBody(b2Body *body, float radiuse);// TODO : see need transfer
	//--------------------------------------------
	// IStatic2DShape
	void			AddToWorld(b2World * world) override;

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
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStatic2DShape
	void			CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	// These visual part player , the part will empty, player not draw
	//CCircleView		m_visual;
};
#pragma once

#include "CircleView.h"

class CBall
	: public CDynamicBody
	, public CDrawable
	, public CCircle
	, private boost::noncopyable

{
public:
	CBall(b2World * world);
	CBall(float radius, const glm::vec2 &position, b2World * world);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void		AddCircleToBody(b2Body *body, float radiuse);// TODO : see need transfer
	//--------------------------------------------
	// IStaticShape
	void			AddToWorld(b2World * world) override;
	//--------------------------------------------
	// CDrawable
	void			Redraw() const;
	bool			HitTest(const glm::vec2 &point) const;
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
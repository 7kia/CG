#pragma once

#include "../World/Wall/WallView.h"
#include "../Mixin/HaveReferenceToC3DShape.h"

#include "Dynamic2DShape.h"
#include "Circle.h"

class C2DCircleCollision
	: public CDynamicBody
	, public CCircle
	, public CHaveReferenceToC3DShape
	, private boost::noncopyable

{
public:
	C2DCircleCollision();
	C2DCircleCollision(float radius, const glm::vec2 &position, C3DShape* pVisual);
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
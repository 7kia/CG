#pragma once

#include "../World/Wall/WallView.h"
#include "../Mixin/HaveReferenceToC3DShape.h"

#include "Dynamic2DShape.h"
#include "Circle.h"

class C2DCircleCollision
	: public CDynamicBody
	, public CCircle
	, private boost::noncopyable

{
public:
	C2DCircleCollision();
	C2DCircleCollision(float radius, const glm::vec2 &position);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void		AddCircleToBody(b2Body *body, float radiuse);// TODO : see need transfer
	//--------------------------------------------
	// IStatic2DShape
	void			AddToWorld(b2World * world) override;

	void			Advance(float dt) override;
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
};
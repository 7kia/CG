#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "../World/Wall/WallView.h"
#include "Static2DShape.h"
#include "Rectangle.h"

class C2DRectangleCollision final
	: public CStatic2DShape
	, public CRectangle
	, private boost::noncopyable
{
public:
	C2DRectangleCollision();
	C2DRectangleCollision(const glm::vec2 & leftTopPoint
		, SSize size
		, float rotate
		);
	virtual ~C2DRectangleCollision() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static void			AddRectangleToBody(b2Body *body
											, SSize size
											, const glm::vec2 & shapeOrigin);// TODO : see need transfer
	//--------------------------------------------
	// IStatic2DShape
	void				AddToWorld(b2World * world) override;
	// Update visual part
	void				Advance(float dt) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStatic2DShape
	void				CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	C3DShape*			m_pVisual = nullptr;
};
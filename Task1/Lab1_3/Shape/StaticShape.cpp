#include "stdafx.h"
#include "StaticShape.h"

CStaticShape::CStaticShape() 
	: IStaticShape()
	, CShape()
{
}

void CStaticShape::AddInWorld(b2World * world)
{
	m_body =world->CreateBody(&m_defBody);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// TODO 
	// The extents are the half-widths of the box.
	//groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	//groundBody->CreateFixture(&groundBox, 0.0f);

}

void CStaticShape::Advance(float dt)
{
	(void)dt;
}

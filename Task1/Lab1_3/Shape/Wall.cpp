#include "stdafx.h"
#include "Wall.h"

CWall::CWall(b2World * world)
	: CStaticShape(world)
	, CDrawable()
	, CRectangle()

{
}

CWall::CWall(const glm::vec2 & leftTopPoint
			, SSize size
			, float rotate
			, const glm::vec3 & outlineColor
			, b2World * world)
	: CStaticShape(world)
	, CDrawable()
	, CRectangle(size)

{
	SetPosition(leftTopPoint);

	m_visual.SetOutlineColor(outlineColor);

	SetRotation(rotate);
}

CWall::~CWall()
{
}

void CWall::AddToWorld(b2World * world)
{
	CheckParametres();
	CStaticShape::AddToWorld(world);
	AddRectangleToBody(m_body
		, SSize(m_width, m_height)
		, GetRotation()
		, GetShapeOrigin());
}

void CWall::Redraw() const
{
	m_visual.Redraw();
}

bool CWall::HitTest(const glm::vec2 & point) const
{
	return m_visual.HitTest(point);
}

void CWall::AddRectangleToBody(b2Body *body
	, SSize size
	, float rotation
	, const glm::vec2 & shapeOrigin)
{
	if ((size.width < 0.f) || (size.height < 0.f))
	{
		throw std::runtime_error("Size will be more zero!!!");
	}

	// Define the ground box shape.
	b2PolygonShape rectangleShape;

	// The extents are the half-widths of the box.
	const glm::vec2 shiftOrigin = { ConvertToBoxCoordinates(size.width) / 2.f, ConvertToBoxCoordinates(size.height) / 2.f };
	rectangleShape.SetAsBox(ConvertToBoxCoordinates(size.width) / 2.f, ConvertToBoxCoordinates(size.height) / 2.f
		, b2Vec2(shapeOrigin.x + shiftOrigin.x, shapeOrigin.y + shiftOrigin.y)
		, 0.f);//SetAsBox(50.0f, 10.0f);

	body->CreateFixture(&rectangleShape, 2.f);
}

void CWall::CheckParametres()
{
	CStaticShape::CheckParametres();

	if (m_width == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define rectangle width!!!");

	}

	if (m_height == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define rectangle height!!!");
	}
}

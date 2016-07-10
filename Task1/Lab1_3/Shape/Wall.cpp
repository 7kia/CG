#include "stdafx.h"
#include "Wall.h"

CWall::CWall()
	: CStaticShape()
	, IShape()
	, CRectangle()

{
}

CWall::CWall(const glm::vec2 & leftTopPoint
			, SSize size
			, float rotate
			, const glm::vec3 & outlineColor
			)
	: CStaticShape()
	, IShape()
	, CRectangle(size)

{
	SetPosition(leftTopPoint);

	m_visual.SetOutlineColor(outlineColor);

	SetRotation(rotate);
}

void CWall::AddToWorld(b2World * world)
{
	CheckParametres();
	CStaticShape::AddToWorld(world);

	SetVisual();
	AddRectangleToBody(m_body
		, SSize(m_width, m_height)
		, GetOrigin());
}

void CWall::Advance(float dt)
{
	(void)dt;
	m_visual.SetPosition(GetPosition());
	m_visual.SetRotation(GetRotation());

}

void CWall::SetVisual()
{
	m_visual.SetWidth(m_width);
	m_visual.SetHeight(m_height);
	m_visual.SetRotation(GetRotation());
	m_visual.SetOrigin(GetOrigin());
	m_visual.SetReferenceSystemOrigin(GetReferenceSystemOrigin());
	m_visual.SetPosition(GetPosition());
}

void CWall::Redraw() const
{
	m_visual.Redraw();
}

bool CWall::HitTest(const glm::vec2 & point) const
{
	return m_visual.HitTest(point);
}

void CWall::SetOutlineColor(const glm::vec3 & color)
{
	m_visual.SetOutlineColor(color);
}

glm::vec3 CWall::GetOutlineColor() const
{
	return m_visual.GetOutlineColor();
}

void CWall::AddRectangleToBody(b2Body *body
	, SSize size
	, const glm::vec2 & shapeOrigin)
{
	if ((size.width < 0.f) || (size.height < 0.f))
	{
		throw std::runtime_error("Size will be more zero!!!");
	}

	// Define the ground box shape.
	b2PolygonShape rectangleShape;

	// Origin body box2d in center by default
	const glm::vec2 shiftOrigin = { Convert::ToBox(size.width) / 2.f, Convert::ToBox(size.height) / 2.f };
	rectangleShape.SetAsBox(Convert::ToBox(size.width) / 2.f, Convert::ToBox(size.height) / 2.f
		, b2Vec2(shapeOrigin.x + shiftOrigin.x, shapeOrigin.y + shiftOrigin.y)
		, 0.f);

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

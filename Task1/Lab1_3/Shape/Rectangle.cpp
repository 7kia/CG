#include "stdafx.h"
#include "Rectangle.h"

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

CRectangle::CRectangle(b2World * world) 
	: CStaticShape(world)
{
}

CRectangle::CRectangle(const glm::vec2 & leftTopPoint
						, SSize size
						, float rotate
						, const glm::vec3 & outlineColor
						, b2World * world)
	: CStaticShape(world)

{
	SetWidth(size.width);
	SetHeight(size.height);
	SetPosition(leftTopPoint);

	SetOutlineColor(outlineColor);

	SetRotation(rotate);
}

CRectangle::~CRectangle()
{
}

void CRectangle::Redraw() const
{

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };
	glm::vec3 shapeOrigin = { GetShapeOrigin().x, GetShapeOrigin().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	//
	transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);
	// ��������� ������ ������� � ���� ������ ��������

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(0.f, 0.f);
	// first triangle
	glVertex2f(0.f, m_height);
	glVertex2f(m_width,m_height);
	// second triangle
	glVertex2f(m_width, 0.f);
	glVertex2f(m_width, m_height);

	glEnd();
	glPopMatrix();


}

bool CRectangle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}

void CRectangle::SetWidth(float width)
{
	if (width < 0)
	{
		m_width = 0;
	}
	else
	{
		m_width = width;
	}
}

float CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetHeight(float height)
{
	if (height < 0)
	{
		m_height = 0;
	}
	else
	{
		m_height = height;
	}
}

float CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AddToWorld(b2World * world)
{
	CheckParametres();
	CStaticShape::AddToWorld(world);
	AddRectangleToBody(m_body
				, SSize(m_width, m_height)
				, GetRotation()
				, GetShapeOrigin());
}

void CRectangle::AddRectangleToBody(b2Body *body
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
	rectangleShape.SetAsBox(ConvertToBoxCoordinates(size.width) /2.f, ConvertToBoxCoordinates(size.height) / 2.f
							, b2Vec2(shapeOrigin.x + shiftOrigin.x, shapeOrigin.y + shiftOrigin.y)
							, 0.f);//SetAsBox(50.0f, 10.0f);

	body->CreateFixture(&rectangleShape, 2.f);
}

void CRectangle::CheckParametres()
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

SSize::SSize()
{
}

SSize::SSize(float width, float height)
	: width(width)
	, height(height)
{
}

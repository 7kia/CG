#include "stdafx.h"
#include "StaticShape.h"

CStaticShape::CStaticShape() 
	: IStaticShape()
	, CShape()
{
	m_defBody.type = b2_staticBody;
}

float ConvertToBoxCoordinates(const float value)
{
	return value / SCALE;
}

glm::vec2 ConvertToBoxCoordinates(const const glm::vec2 & value)
{
	return glm::vec2(ConvertToBoxCoordinates(value.x) , ConvertToBoxCoordinates(value.y));
}

float ConvertToNormalCoordinates(const float value)
{
	return value * SCALE;
}

glm::vec2 ConvertToNormalCoordinates(const glm::vec2 & value)
{
	return glm::vec2(ConvertToNormalCoordinates(value.x), ConvertToNormalCoordinates(value.y));
}


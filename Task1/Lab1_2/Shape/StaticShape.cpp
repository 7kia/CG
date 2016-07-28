#include "stdafx.h"
#include "StaticShape.h"

CStaticShape::CStaticShape() 
	: IStaticShape()
	, CDrawable()
	, CHaveOrigin()
	, CHavePosition()

{
	SetPosition(NONE_VALUE::GLM_VEC2);

	m_referenceSystemOrigin = NONE_VALUE::GLM_VEC2;
}

void CStaticShape::CheckParametres()
{
	if (GetPosition() == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define position!!!");
	}

	/*// TODO : see need define this
		if (m_defBody.angle == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define angle!!!");
	}

	*/

	if (m_referenceSystemOrigin == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define reference system origin!!!");
	}

	/* // TODO : see need define this
		if (m_shapeOrigin == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define shape origin!!!");
	}

	*/

}


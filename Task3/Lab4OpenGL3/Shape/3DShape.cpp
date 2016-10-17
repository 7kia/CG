#include "stdafx.h"
#include "3DShape.h"

I3DShape::I3DShape()
	: IDrawable()
{
}

CIdentity3DShape::CIdentity3DShape(MeshType meshType)
	: C3DShape()
	, SMeshDataP3NT2()
	, m_mesh(meshType)
{
}

void CIdentity3DShape::Draw(IRenderer3D &renderer) const
{
	m_mesh.Draw(renderer);
}

C3DShape::C3DShape()
	: I3DShape()
	, CTransformable()
{
}


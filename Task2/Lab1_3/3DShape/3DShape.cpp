#include "stdafx.h"
#include "3DShape.h"

I3DShape::I3DShape()
	: IDrawable()
{
}

CIdentity3DShape::CIdentity3DShape()
	: C3DShape()
	, CHaveVertexes()

{
}

void CIdentity3DShape::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));

	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});

	glPopMatrix();
}

C3DShape::C3DShape()
	: I3DShape()
	, CTransformable()
{
}

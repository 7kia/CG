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

std::vector<SVertexP3NT2> CIdentity3DShape::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for //(const auto & index : m_indicies)
		(size_t index = 0; index < m_vertices.size(); ++index)
	{
		auto vertexWithTransform = m_vertices[index];
		vertexWithTransform.position = GetVertexPosition(index);
		result.push_back(vertexWithTransform);
	}
	return result;
}

glm::vec3 CIdentity3DShape::GetVertexPosition(uint index) const
{
	CheckVertexIndex(index);

	auto currentPosition = glm::translate(GetTransform(), m_vertices[index].position);
	return glm::vec3(currentPosition[3][0], currentPosition[3][1], currentPosition[3][2]);
}



C3DShape::C3DShape()
	: I3DShape()
	, CTransformable()
{
}

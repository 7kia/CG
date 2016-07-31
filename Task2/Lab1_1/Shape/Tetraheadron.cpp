//#include "../stdafx.h"
#include "stdafx.h"
#include "Tetrahedron.h"

namespace
{

	// Сторона тетраэдра равна √3,
	// расстояние от центра грани до вершины равно 1.
	const Vertex TETRAHEDRON_VERTICES[] = {
		{ 0.f, 0.f, -1.0f },
		{ 0.f, 0.f , 0.f },//{ 0.f, 0.f , 0.f },
		{ 0.5f, -sqrtf(3.f) / 2.f, 0.f },//{ 0.5f, -sqrtf(3.f) / 2.f, 0.f },
		{ -0.5f, -sqrtf(3.f) / 2.f, 0.f },//{ -0.5f, -sqrtf(3.f) / 2.f, 0.f }
	};


	const STriangleFace TETRAHEDRON_FACES[] = {
		{ 0, 1, 2, 0 },
		{ 0, 3, 1, 0 },
		{ 2, 1, 3, 0 },
		{ 0, 2, 3, 0 },
	};

}


CTetrahedron::CTetrahedron()
	: CTransparentShape()
	, IUpdatable()
{
}

void CTetrahedron::Update(float deltaTime)
{
	(void)deltaTime;
}

void CTetrahedron::DrawOutputFaces() const
{
	// менее оптимальный способ рисования: прямая отправка данных
	// могла бы работать быстрее, чем множество вызовов glColor/glVertex.
	glBegin(GL_TRIANGLES);

	for (const STriangleFace &face : TETRAHEDRON_FACES)
	{
		const Vertex &v1 = TETRAHEDRON_VERTICES[face.vertexIndex1];
		const Vertex &v2 = TETRAHEDRON_VERTICES[face.vertexIndex2];
		const Vertex &v3 = TETRAHEDRON_VERTICES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		glColor4fv(glm::value_ptr(GetFaceColor()));
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
}

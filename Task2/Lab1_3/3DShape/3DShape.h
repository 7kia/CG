#pragma once
#include <memory>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

#include <GL/glew.h>
#include <GL/glu.h>
#include <boost/noncopyable.hpp>

#include <iterator>
#include <algorithm>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>


#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"
#include "../Mixin/HaveVertex.h"
#include "../Mixin/Transformable.h"


namespace// TODO : rewrite this namespace
{
	typedef glm::vec3 Vertex;

	struct STriangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t colorIndex;
	};

	/// Привязывает вершины к состоянию OpenGL,
	/// затем вызывает 'callback'.
	template <class T>
	void DoWithBindedArrays(const std::vector<SVertexP3NT2> &vertices, T && callback)
	{
		// Включаем режим vertex array и normal array.
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// Выполняем привязку vertex array и normal array
		const size_t stride = sizeof(SVertexP3NT2);
		glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
		glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));
		glTexCoordPointer(2, GL_FLOAT, stride, glm::value_ptr(vertices[0].texCoord));

		// Выполняем внешнюю функцию.
		callback();

		// Выключаем режим vertex array и normal array.
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

}


class I3DShape
	: public IDrawable
{
public:
	I3DShape();
    virtual ~I3DShape() = default;
};

class C3DShape
	: public I3DShape
	, public CTransformable

{
public:
	C3DShape();
};

class CIdentity3DShape
	: public C3DShape
	, public CHaveVertexes
{
public:
	CIdentity3DShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IDrawable
	void							Draw() const override;
	//--------------------------------------------

	std::vector<SVertexP3NT2>		GetVertexes() const override;
	glm::vec3						GetVertexPosition(uint index) const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:

};

using IBodySharedPtr = std::shared_ptr<C3DShape>;
using IdentityShapeSharedPtr = std::shared_ptr<CIdentity3DShape>;

IdentityShapeSharedPtr Weld(const IdentityShapeSharedPtr first
							, const IdentityShapeSharedPtr second
							, size_t firstIndex
							, size_t secondIndex);

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

	void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
		unsigned columnCount, unsigned rowCount)
	{
		indicies.clear();
		indicies.reserve((columnCount - 1) * rowCount * 2);
		// вычисляем индексы вершин.
		for (unsigned ci = 0; ci < columnCount - 1; ++ci)
		{
			if (ci % 2 == 0)
			{
				for (unsigned ri = 0; ri < rowCount; ++ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index + rowCount);
					indicies.push_back(index);
				}
			}
			else
			{
				for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index);
					indicies.push_back(index + rowCount);
				}
			}
		}
	}

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
protected:
	virtual void					DrawOutputFaces() const {};

//////////////////////////////////////////////////////////////////////
// Data
protected:

};

using IBodyUniquePtr = std::unique_ptr<C3DShape>;

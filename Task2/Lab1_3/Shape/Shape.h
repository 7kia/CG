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
#include "../Mixin/HaveFaceColor.h"
#include "../Mixin/Transformable.h"

// Вершина с трёхмерной позицией, нормалью и 2D координатами текстуры.
struct SVertexP3NT2
{
	SVertexP3NT2() = default;
	SVertexP3NT2(const glm::vec3 & position
				, const glm::vec2 & texCoord
				, const glm::vec3 & normal);

	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

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
}


class IShape
	: public IDrawable
	, public IUpdatable
{
public:
	IShape();
    virtual ~IShape() = default;
};

class CShape
	: public IShape
{
public:
	CShape();
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
	std::vector<SVertexP3NT2>		m_vertices;
	std::vector<uint32_t>			m_indicies;

};

using IBodyUniquePtr = std::unique_ptr<IShape>;

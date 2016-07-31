#pragma once
#include <memory>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <GL/glew.h>
#include <GL/glu.h>
#include <boost/noncopyable.hpp>

#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"
#include "../Mixin/HaveFaceColor.h"
#include "../Mixin/Transformable.h"

namespace
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
	: public CHaveFaceColor
	, public IShape
	, public CTransformable
{
public:
	CShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			Draw() const override;
protected:
	virtual void	DrawOutputFaces() const {};
};

using IBodyUniquePtr = std::unique_ptr<CShape>;

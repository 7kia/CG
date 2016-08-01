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
	, public IHaveFaceColor
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
	void			Draw() const override;
	//--------------------------------------------
	// IHaveFaceColor
	void					SetFaceColor(const glm::vec4 &color) override;
	glm::vec4				GetFaceColor() const override;

	void					SetAlpha(float alpha) override;
	float					GetAlpha() const override;
	//--------------------------------------------

protected:
	virtual void			DrawOutputFaces() const {};
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4				m_faceColor;

};

using IBodyUniquePtr = std::unique_ptr<IShape>;

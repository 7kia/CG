#pragma once

#include "../Shape/Shape.h"
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>


class IAbstractShapeDecorator
{
public:
	virtual ~IAbstractShapeDecorator() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void UpdateChild(float deltaTime) = 0;
	virtual void DrawChild() const = 0;

};

class CAbstractShapeDecorator 
	: public IShape
	//, public IAbstractShapeDecorator
{
public:
	CAbstractShapeDecorator();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void SetChild(IBodyUniquePtr && pChild);
protected:
	//--------------------------------------------
	// IShape
	void Update(float deltaTime) override;
	void Draw() const override;
	//--------------------------------------------
	// IHaveFaceColor
	void					SetFaceColor(const glm::vec4 &color) override;
	glm::vec4				GetFaceColor() const override;

	void					SetAlpha(float alpha) override;
	float					GetAlpha() const override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
protected:
	IBodyUniquePtr m_pChild;
};

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
	void					Update(float deltaTime) override;
	void					Draw() const override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
protected:
	IBodyUniquePtr			m_pChild;
};
#pragma once

#include "../IBody.h"
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>

class CAbstractShapeDecorator : public IShape
{
public:
	void SetChild(IBodyUniquePtr && pChild);

protected:
	void UpdateChild(float deltaTime);
	void DrawChild()const;

private:
	IBodyUniquePtr m_pChild;
};

#pragma once

#include <array>

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Pentagon.h"

class CDodecahedron final
	: public ÑCompositeShape
{
public:
	CDodecahedron();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	//--------------------------------------------
private:
	void					CreatePentagon(const std::array<glm::vec3, 6> & points);
};

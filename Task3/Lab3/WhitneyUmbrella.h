#pragma once

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <Shape\3DShape.h>

// TODO : delete
// Вершина с трёхмерной позицией и нормалью.
struct SVertexP3N
{
    glm::vec3 position;
    glm::vec3 normal;
};

// Класс поверхности "Зонтик Уитни"
// https://en.wikipedia.org/wiki/Whitney_umbrella
class CLine
	: public CIdentity3DShape
{
public:
    CLine(float length, size_t amountVertex);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IDrawable
    void Draw()const override;
	//--------------------------------------------
private:
    void Tesselate(unsigned slices, unsigned stacks);
//////////////////////////////////////////////////////////////////////
// Data
};

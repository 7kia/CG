#pragma once

#include "IShape.h"
#include "../Mixin/TransparentShape.h"

namespace CubeSpace
{

enum class CubeFace
{
	Front = 0,
	Back,
	Top,
	Bottom,
	Left,
	Right,

	NumFaces
};

// Привыкаем использовать 16-битный unsigned short,
// чтобы экономить память на фигурах с тысячами вершин.
const STriangleFace CUBE_FACES[] = {
	{ 0, 1, 2, static_cast<uint16_t>(CubeFace::Back) },
	{ 0, 2, 3, static_cast<uint16_t>(CubeFace::Back) },
	{ 2, 1, 5, static_cast<uint16_t>(CubeFace::Right) },
	{ 2, 5, 6, static_cast<uint16_t>(CubeFace::Right) },
	{ 3, 2, 6, static_cast<uint16_t>(CubeFace::Bottom) },
	{ 3, 6, 7, static_cast<uint16_t>(CubeFace::Bottom) },
	{ 0, 3, 7, static_cast<uint16_t>(CubeFace::Left) },
	{ 0, 7, 4, static_cast<uint16_t>(CubeFace::Left) },
	{ 1, 0, 4, static_cast<uint16_t>(CubeFace::Top) },
	{ 1, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
	{ 6, 5, 4, static_cast<uint16_t>(CubeFace::Front) },
	{ 6, 4, 7, static_cast<uint16_t>(CubeFace::Front) },
};

// Вершины куба служат материалом для формирования треугольников,
// составляющих грани куба.
const Vertex CUBE_VERTICIES[] = {
	{ -1, +1, -1 },
	{ +1, +1, -1 },
	{ +1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, +1, +1 },
	{ +1, +1, +1 },
	{ +1, -1, +1 },
	{ -1, -1, +1 },
};

}

class CIdentityCube final 
	: public CTransparentShape
{
public:
	CIdentityCube();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void Update(float deltaTime) override final;
	//--------------------------------------------
	// Color
	void SetFaceColor(CubeSpace::CubeFace face, const glm::vec4 &color);// TODO : see can this rewrite by help mixin
	void SetAlpha(float alpha);
	//--------------------------------------------
private:
	//--------------------------------------------
	// CTransparentShape
	void DrawOutputFaces() const override final;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	static const size_t COLORS_COUNT = static_cast<size_t>(CubeSpace::CubeFace::NumFaces);
	glm::vec4 m_colors[COLORS_COUNT];
	float m_alpha;
};

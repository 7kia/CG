#pragma once

#include "IShape.h"


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

// ��������� ������������ 16-������ unsigned short,
// ����� ��������� ������ �� ������� � �������� ������.
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

// ������� ���� ������ ���������� ��� ������������ �������������,
// ������������ ����� ����.
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

class CIdentityCube final : public IShape
{
public:
	CIdentityCube();
	void Update(float deltaTime) final;
	void Draw()const final;

	void SetFaceColor(CubeSpace::CubeFace face, const glm::vec3 &color);
	void SetAlpha(float alpha);

private:
	void OutputFaces()const;

	static const size_t COLORS_COUNT = static_cast<size_t>(CubeSpace::CubeFace::NumFaces);
	glm::vec3 m_colors[COLORS_COUNT];
	float m_alpha;
};

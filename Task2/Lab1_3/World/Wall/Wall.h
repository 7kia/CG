#pragma once

#include "../../Shape3D/3DRectangle.h"
#include <array>
#include "WallType.h"

namespace WallSpace
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

	struct SRectangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t vertexIndex4;
		uint16_t colorIndex;
	};


	const SRectangleFace CUBE_FACES[] = {
		{ 5, 4, 7, 6, static_cast<uint16_t>(CubeFace::Front) },
		{ 0, 1, 2, 3, static_cast<uint16_t>(CubeFace::Back) },
		{ 1, 0, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
		{ 3, 2, 6, 7, static_cast<uint16_t>(CubeFace::Bottom) },
		{ 4, 0, 3, 7, static_cast<uint16_t>(CubeFace::Left) },
		{ 1, 5, 6, 2, static_cast<uint16_t>(CubeFace::Right) },
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

	static const float SIZE = 2.f;
}

class CWall final
	: public СComposite3DShape
{
public:
	CWall();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// C3DShape
	void						Update(float deltaTime) override final;
	void						Draw() const override final;
	//--------------------------------------------

	void						SetType(const CWallType* type);
	const CWallType*			GetType() const;
	//
	void						SetVisible(uint index, bool value);
	bool						GetVisible(uint index) const;

	void						CheckVisibleIndex(uint index) const;
private:
	CTexture2D*					GetTexture() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::array<bool, 6>				m_visible;
	const CWallType*				m_pType;
};

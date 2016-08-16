#pragma once

#include "../../3DShape/3DRectangle.h"
#include "../../Mixin/HaveVisiblePart.h"
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

	// TODO: protect my privacy
	struct SRectangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t vertexIndex4;
		uint16_t colorIndex;
	};


	// TODO: protect my privacy
	const SRectangleFace CUBE_FACES[] = {
		{ 5, 4, 7, 6, static_cast<uint16_t>(CubeFace::Front) },
		{ 0, 1, 2, 3, static_cast<uint16_t>(CubeFace::Back) },
		{ 1, 0, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
		{ 3, 2, 6, 7, static_cast<uint16_t>(CubeFace::Bottom) },
		{ 4, 0, 3, 7, static_cast<uint16_t>(CubeFace::Left) },
		{ 1, 5, 6, 2, static_cast<uint16_t>(CubeFace::Right) },
	};

	// TODO: protect my privacy
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

class CWallView final
	: public СComposite3DShape
	, public IHavePointerToWallViewType
	, public CHaveVisiblePart
{
public:
	CWallView();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CIdentity3DShape
	void						Draw() const override final;
	//--------------------------------------------
	// IHavePointerToWallViewType
	void						SetType(const CWallViewType* type) override;
	const CWallViewType*		GetType() const override;
	//--------------------------------------------
	// ITransformable
	void						SetTransform(const glm::mat4 &transform) override;
	//--------------------------------------------
private:
	CTexture2D*					GetTexture() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	const CWallViewType*		m_pType; // TODO: nullptrize me
};

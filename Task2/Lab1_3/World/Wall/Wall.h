#pragma once

#include "../Actor.h"
#include "../../2DShape/2DRectangleCollision.h"
#include "../../Mixin/Have3DPosition.h"
#include "WallView.h"

#include <glm\mat4x4.hpp>

class CWall final
	: public IActor
	, public ITransformable
	, public IHave3DPosition
	, public IHavePointerToWallViewType
	, public IHaveVisiblePart
{
public:
	CWall();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IActor
	void							Draw() const override;
	void							Update(float deltaTime) override;
	//--------------------------------------------
	// IHavePointerToWallViewType
	void							SetType(const CWallViewType* type) override;
	const CWallViewType*			GetType() const override;
	//--------------------------------------------
	// IHaveVisiblePart
	void							SetVisible(bool value) override;
	void							SetVisible(size_t index, bool value) override;
	bool							GetVisible(size_t index) const override;


	void							CheckVisibleIndex(size_t index) const override;
	//--------------------------------------------
	// IHave3DPosition
	void							SetPosition(const glm::vec3 &value) override;
	glm::vec3						GetPosition() const override;

	void							Move(const glm::vec3 &value) override;
	//--------------------------------------------
	// ITransformable
	void							SetTransform(const glm::mat4 &transform) override;// TODO : see might would need "final"
	glm::mat4						GetTransform() const override;
	//--------------------------------------------

	void							AddToWorld(b2World * world);
	void							SetHaveCollision(bool value);
	bool							GetHaveCollision() const;


	// for buiding labyrinth
	const CWallView*				GetVisual() const;
private:
	bool							CheckContentCollision() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	CWallView										m_visual;

	bool											m_haveCollision = false;
	std::shared_ptr<C2DRectangleCollision>			m_collision; // TODO: why shared_ptr
};

using PWall = std::shared_ptr<CWall>;

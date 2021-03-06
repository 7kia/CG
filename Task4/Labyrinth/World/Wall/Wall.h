#pragma once

#include "World/Actor/Actor.h"
#include "2DShape/2DRectangleCollision.h"
#include "Mixin/Have3DPosition.h"
#include "WallView.h"

#include <glm\mat4x4.hpp>

class CWall final
	: public CActor
	, public ITransformable
	, public IHave3DPosition
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
	void							SetType(const CWallViewType* type);
	const CWallViewType*			GetType() const;
	//--------------------------------------------
	// IHaveVisiblePart
	void							SetVisible(bool value) override;
	void							SetVisible(size_t index, bool value) override;
	bool							GetVisible(size_t index) const override;
	//--------------------------------------------
	// IHave3DPosition
	void							SetPosition(const glm::vec3 &value) override;
	glm::vec3						GetPosition() const override;

	void							Move(const glm::vec3 &value) override;
	//--------------------------------------------
	// ITransformable
	void							SetTransform(const glm::mat4 &transform) override;
	glm::mat4						GetTransform() const override;
	//--------------------------------------------

	void							AddToWorld(b2World * world);
	void							SetHaveCollision(bool value);
	bool							GetHaveCollision() const;


	// for buiding labyrinth
	const CWallView*				GetVisual() const;
private:
	void							CheckVisibleIndex(size_t index) const override;

	bool							CheckContentCollision() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	CWallView										m_visual;

	bool											m_haveCollision = false;

	// is shared_ptr because allocate memory if need collision
	std::shared_ptr<C2DRectangleCollision>			m_collision; 
};

using PWall = std::shared_ptr<CWall>;

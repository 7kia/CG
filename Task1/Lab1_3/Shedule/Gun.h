#pragma once

#include "../Shape/StaticShape.h"
#include "../Shape/Ball.h"
#include "../Shape/Wall.h"

class CPhysicalSystem;

namespace DEFAULT_GUN
{
	static const float SHIFT_BALL = 50.f;
	static const float SHIFT_TRUNK = 5.f;

}

class CGun final
	: public CStaticShape
	, public CDrawable
{
public:
	CGun(b2World * world);
	~CGun();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void				Redraw() const override;
	bool				HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
	// CHaveOrigin
	void				SetPosition(const glm::vec2 & position) override;
	void				SetPosition(float x, float y) override;

	glm::vec2			GetCenterPosition(const glm::vec2 & origin) const override;
	glm::vec2			GetCenterPosition() const override;

	void				SetReferenceSystemOrigin(const glm::vec2 & origin) override;
	//--------------------------------------------
	// IRotatable
	void				SetRotation(float rotation) override;
	float				GetRotation() const override;
	//--------------------------------------------
	// IStaticShape
	void				AddToWorld(b2World * world) override;

	// Update visual part
	void				Advance(float dt) override;
	// Set visual part before create body, because view can have
	// different from body
	void				SetVisual() override;
	//--------------------------------------------

	void				Rotate(const glm::vec2 & mousePosition);

	void				Shoot(CPhysicalSystem * system, const glm::vec2 & mousePosition);
	glm::vec2			GetDirection(const glm::vec2 & point);
//////////////////////////////////////////////////////////////////////
// Methods
private:
	//--------------------------------------------
	// IStaticShape
	void				CreateBody(float trunkWidth
									, float trunkHeigth
									, float baseRadius);
	void				CheckParametres() override;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<std::shared_ptr<CShape>>		m_visual;
};
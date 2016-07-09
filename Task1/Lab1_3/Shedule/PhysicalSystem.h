#pragma once

#include <SDL2/SDL_events.h>

#include "../Shape/DynamicShape.h"
#include "../Shape/Ball.h"
#include "../Shape/Wall.h"
#include "Gun.h"

#include <vector>
#include <memory>

static const size_t AMOUNT_OBSTACLES = 7;
//static const b2Vec2 GRAVITY(0.0f, -10.f);

//static b2World						m_world(b2Vec2(0.0f, -10.f));


class CPhysicalSystem
{
public:
    CPhysicalSystem(float windowWidth, float windowHeight);
    ~CPhysicalSystem();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void											AddShape(std::shared_ptr<CDrawable> particle);

    // @param dt - разница во времени с предыдущим вызовом Advance.
    void											Advance(float dt);
    void											Draw() const;
	void											Redraw() const;

	void											SetPosition(const glm::vec2 & position);
	glm::vec2										GetPosition() const;

	void											SetPlaceSize(const glm::vec2 &value);
	glm::vec2										GetPlaceSize() const;

	b2World*										GetWorld();// must be not constant

	void											ProcessCollisions(float dt);
	//--------------------------------------------
	// Accept command from window
	bool											OnDragBegin(const glm::vec2 & position);
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Methods
private:
	void											CreateWall(const glm::vec2 & leftTopPoint
																, float width
																, float height
																, float rotation
																, const glm::vec3 & outlineColor);

	void											SetMaxAmountBalls(size_t amount);
	size_t											GetMaxAmountBalls();

	bool											CheckExitFromBorder(const glm::vec2 & particlePosition);
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::shared_ptr<CDrawable>>			m_shapes;//CStaticShape
	std::weak_ptr<CGun>								m_gun;
	CShape*											m_draggingShape = nullptr;
	//////////////////////////////////////////////////////////////////////
// Data
private:
	std::shared_ptr<b2World>						m_world;

	glm::vec2										m_placeSize;
	glm::vec2										m_position;// TODO : fix name
	size_t											m_maxAmountBalls = 50 + AMOUNT_OBSTACLES;
//////////////////////////////////////////////////////////////////////
};

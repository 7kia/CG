#pragma once

#include "../Shape/DynamicShape.h"
#include "../Shape/Ball.h"
#include "../Shape/Rectangle.h"

#include <vector>
#include <memory>

class CPhysicalSystem
{
public:
    CPhysicalSystem();
    ~CPhysicalSystem();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void											AddShape(std::shared_ptr<CStaticShape> particle);

    // @param dt - разница во времени с предыдущим вызовом Advance.
    void											Advance(float dt);
    void											Draw() const;
	void											Redraw() const;

	void											SetPosition(const glm::vec2 & position);

	void											SetPlaceSize(const glm::vec2 &value);
	glm::vec2										GetPlaceSize() const;


	void											ProcessCollisions();
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void											SetMaxAmountBalls(size_t amount);
	size_t											GetMaxAmountBalls();

	bool											CheckExitFromBorder(const glm::vec2 & particlePosition);
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::shared_ptr<CStaticShape>>		m_shapes;
	CShape*											m_draggingShape = nullptr;
	//////////////////////////////////////////////////////////////////////
// Data
private:
	glm::vec2										m_placeSize;
	size_t											m_maxAmountBalls = 50;
//////////////////////////////////////////////////////////////////////
};

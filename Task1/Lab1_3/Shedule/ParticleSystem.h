#pragma once

#include "DynamicParticle.h"

class CPhysicalSystem
{
public:
    CPhysicalSystem();
    ~CPhysicalSystem();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void											AddParticles(std::unique_ptr<CDynamicParticle> particle);

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
	void											SetMaxAmountParticles(size_t amount);
	size_t											GetMaxAmountParticles();

	bool											CheckExitFromBorder(const glm::vec2 & particlePosition);
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::unique_ptr<CDynamicParticle>>	m_particles;
	CDynamicParticle*								m_draggingParticle = nullptr;
	//////////////////////////////////////////////////////////////////////
// Data
private:
	glm::vec2										m_placeSize;
	size_t											m_maxAmountParticles = 50;
//////////////////////////////////////////////////////////////////////
};

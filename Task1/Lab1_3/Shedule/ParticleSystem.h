#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"

static const float ELECTRIC_CONSTANT = 8.f;//8,85418781762·10−12 слишком мала для расчётов
static const float K_IN_COULOMB_LAW = 1.f / (4.f * float(M_PI) * ELECTRIC_CONSTANT);
static const float ELECTRON_MASS = 0.005f;
static const float PROTON_MASS = 0.005f;

static const float MIN_DISTANCE = 6.f * DEFAULT_PARTICLE::RADIUSE;
static const float MIN_POWER_FOR_INTERACTION = K_IN_COULOMB_LAW 
												/ MIN_DISTANCE;

class CPhysicalSystem
{
public:
    CPhysicalSystem();
    ~CPhysicalSystem();
//////////////////////////////////////////////////////////////////////
// Methods
public:
    void											SetEmitter(std::unique_ptr<CParticleEmitter> && pEmitter);

	void											AddParticles(std::unique_ptr<CDynamicParticle> particle);

    // @param dt - разница во времени с предыдущим вызовом Advance.
    void											Advance(float dt);
    void											Draw() const;
	void											Redraw() const;

	void											SetPosition(const glm::vec2 & position);

	void											ProcessCollisions();
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void											SetMaxAmountParticles(size_t amount);
	size_t											GetMaxAmountParticles();

	bool											CheckExitFromBorder(const glm::vec2 & particlePosition);


	//
	float											GetPower(CDynamicParticle & first, CDynamicParticle & second);

	float											GetParticleCharge(bool sign);
	float											GetAccelerationParticle(bool sign, float power);

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::unique_ptr<CDynamicParticle>>	m_particles;
	CDynamicParticle*								m_draggingParticle = nullptr;
	//////////////////////////////////////////////////////////////////////
// Data
private:
    std::unique_ptr<CParticleEmitter>				m_pEmitter;
	size_t											m_maxAmountParticles = 25;
//////////////////////////////////////////////////////////////////////
};

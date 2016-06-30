#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"

static const float ELECTRIC_CONSTANT = 8.f;//8,85418781762·10−12 слишком мала для расчётов
static const float K_IN_COULOMB_LAW = 1.f / (4 * M_PI * ELECTRIC_CONSTANT);
static const float MIN_POWER_FOR_INTERACTION = 0.00000625f;
static const float ELECTRON_MASSA = 1.f;
static const float PROTON_MASSA = 1.f;


class CParticleSystem
{
public:
    CParticleSystem();
    ~CParticleSystem();
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
	float											GetPower(std::unique_ptr<CDynamicParticle> & first
															, std::unique_ptr<CDynamicParticle> & second);

	float											GetChargeParticle(bool sign);
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
	size_t											m_maxAmountParticles = 2;
//////////////////////////////////////////////////////////////////////
};

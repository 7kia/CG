#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"

static const float ELECTRIC_CONSTANT = 8.f;//8,85418781762·10−12 слишком мала для расчётов
static const float K_IN_COULOMB_LAW = 1.f / (4.f * float(M_PI) * ELECTRIC_CONSTANT);

static const float ELECTRON_CHARGE = -1.f;// 1.60217662e-19
static const float PROTON_CHARGE = 1.f;
static const float ELECTRON_MASSA = 0.0001f;//1.60217662e-19f
static const float PROTON_MASSA = 0.0001f;//1.60217662e-19f

static const float MIN_DISTANCE = 6.f * DEFAULT_PARTICLE::RADIUSE;
static const float MIN_POWER_FOR_INTERACTION = K_IN_COULOMB_LAW * ELECTRON_MASSA * PROTON_MASSA
												/ (MIN_DISTANCE * MIN_DISTANCE);
static const float EPSILON_DISTANCE = 2.f;
static const float MIN_DISTANCE_BETWEEN_PARTICLE = DEFAULT_PARTICLE::RADIUSE * 2.f;

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
	glm::vec2										GetPower(std::unique_ptr<CDynamicParticle> & first
															, std::unique_ptr<CDynamicParticle> & second);

	float											GetChargeParticle(bool sign);
	glm::vec2										GetAccelerationParticle(bool sign, const glm::vec2 & power);

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

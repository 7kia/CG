#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"

static const float ELECTRIC_CONSTANT = 10*8.85418781762e-0f;//8,85418781762·10−12 слишком мала для расчётов
static const float K_IN_COULOMB_LAW = 1.f / (4.f * float(M_PI) * ELECTRIC_CONSTANT);

static const float ELECTRON_CHARGE = -2.f;// 1.60217662e-19
static const float PROTON_CHARGE = 2.f;
static const float ELECTRON_MASS = 1.60217662e-9f;//1.60217662e-19f
static const float PROTON_MASS = 1.60217662e-9f;//1.60217662e-19f

static const float MIN_DISTANCE = 6.f * DEFAULT_PARTICLE::RADIUSE;
static const float MIN_POWER_FOR_INTERACTION = K_IN_COULOMB_LAW * ELECTRON_MASS * PROTON_MASS
												/ (MIN_DISTANCE * MIN_DISTANCE);
static const float EPSILON_DISTANCE = 4.f;
static const float MIN_DISTANCE_BETWEEN_PARTICLE = DEFAULT_PARTICLE::RADIUSE * 2.f;

glm::vec2			GetPower(std::unique_ptr<CDynamicParticle> & first
							, std::unique_ptr<CDynamicParticle> & second);

float				GetParticleCharge(bool sign);
glm::vec2			GetParticleAcceleration(bool sign, const glm::vec2 & power);


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
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::unique_ptr<CDynamicParticle>>	m_particles;
	CDynamicParticle*								m_draggingParticle = nullptr;
	//////////////////////////////////////////////////////////////////////
// Data
private:
    std::unique_ptr<CParticleEmitter>				m_pEmitter;
	size_t											m_maxAmountParticles = 20;
//////////////////////////////////////////////////////////////////////
};

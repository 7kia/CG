#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"
#include <functional>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGTH = 600;


static const float ELECTRIC_CONSTANT = 10*8.85418781762e-0f;//8,85418781762·10−12 слишком мала для расчётов
static const float K_IN_COULOMB_LAW = 1.f / (4.f * float(M_PI) * ELECTRIC_CONSTANT);

static const float ELECTRON_CHARGE = -2.f;// 1.60217662e-19
static const float PROTON_CHARGE = 2.f;

static const float MIN_DISTANCE = 6.f * DEFAULT_PARTICLE::RADIUSE;
static const float MIN_POWER_FOR_INTERACTION = K_IN_COULOMB_LAW * ELECTRON_MASS * PROTON_MASS
												/ (MIN_DISTANCE * MIN_DISTANCE * MIN_DISTANCE);

static const float EPSILON_DISTANCE = 4.f;
static const float MIN_DISTANCE_BETWEEN_PARTICLE = DEFAULT_PARTICLE::RADIUSE * 2.f;

glm::vec2			GetPower(std::shared_ptr<CStaticParticle> & first
							, std::shared_ptr<CStaticParticle> & second);

float				GetParticleCharge(bool sign);
glm::vec2			GetParticleAcceleration(bool sign, const glm::vec2 & power);

std::shared_ptr<CStaticParticle> Lock(std::weak_ptr<CStaticParticle> pointer);

class CParticleSystem
{
public:
    CParticleSystem();
    ~CParticleSystem();
//////////////////////////////////////////////////////////////////////
// Methods
public:
    void											SetEmitter(std::unique_ptr<CParticleEmitter> && pEmitter);

	void											AddParticles(std::shared_ptr<CStaticParticle> particle);

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
	std::vector<std::shared_ptr<CStaticParticle>>	m_particles;
	std::weak_ptr<CStaticParticle>					m_draggingParticle;
//////////////////////////////////////////////////////////////////////
// Data
private:
    std::unique_ptr<CParticleEmitter>				m_pEmitter;
	size_t											m_maxAmountParticles = 24;
//////////////////////////////////////////////////////////////////////
};

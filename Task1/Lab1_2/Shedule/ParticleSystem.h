#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include "ParticleEmitter.h"

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
	//////////////////////////////////////////////////////////////////////
// Data
private:
    std::unique_ptr<CParticleEmitter>				m_pEmitter;
	size_t											m_maxAmountParticles = 2;
//////////////////////////////////////////////////////////////////////
};

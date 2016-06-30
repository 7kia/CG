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

    // @param dt - разница во времени с предыдущим вызовом Advance.
    void											Advance(float dt);
    void											Draw() const;
	void											Redraw() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
    std::unique_ptr<CParticleEmitter>				m_pEmitter;
    std::vector<std::unique_ptr<CDynamicParticle>>	m_particles;
//////////////////////////////////////////////////////////////////////
};

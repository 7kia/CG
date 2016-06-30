#include "stdafx.h"
#include "ParticleSystem.h"

#include <limits>
#include <algorithm>


CParticleSystem::CParticleSystem() = default;
CParticleSystem::~CParticleSystem() = default;

void CParticleSystem::SetEmitter(std::unique_ptr<CParticleEmitter> &&pEmitter)
{
    m_pEmitter = std::move(pEmitter);
}

void CParticleSystem::Advance(float dt)
{
    // Генерируем новые частицы
    m_pEmitter->Advance(dt);
    // За 1 кадр может появиться несколько новых частиц.
    while (m_pEmitter->IsEmitReady())
    {
        m_particles.emplace_back(m_pEmitter->Emit());
    }
    // Продвигаем время жизни всех цветов.
    for (const auto &pParticle : m_particles)
    {
        pParticle->Advance(dt, GRAVITY);
    }
    // Удаляем "умершие" цветы.
    auto newEnd = std::remove_if(m_particles.begin(), m_particles.end(), [](const auto &pParticle) {
        return !pParticle->IsAlive();
    });
    m_particles.erase(newEnd, m_particles.end());
}

void CParticleSystem::Draw()
{
    for (const auto &pParticle : m_particles)
    {
        pParticle->Draw();
    }
}

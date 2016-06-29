#include "stdafx.h"
#include "ParticleSystem.h"
#include <limits>
#include <algorithm>
namespace
{
const glm::vec2 GRAVITY = {0.f, 9.8f};
}

void CDynamicParticle::Advance(float dt, const glm::vec2 &acceleration)
{
    m_lifetime -= dt;
    m_velocity += dt * acceleration;
    SetPosition(m_velocity + GetPosition());
}

bool CDynamicParticle::IsAlive() const
{
    const float epsilon = std::numeric_limits<float>::epsilon();
    return m_lifetime > epsilon;
}

glm::vec2 CDynamicParticle::GetVelocity() const
{
    return m_velocity;
}

void CDynamicParticle::SetVelocity(const glm::vec2 &velocity)
{
    m_velocity = velocity;
}

void CDynamicParticle::SetLifetime(float lifetime)
{
    m_lifetime = lifetime;
}

CParticleEmitter::CParticleEmitter()
{
    std::random_device rd;
    m_random.seed(rd());
}

void CParticleEmitter::Advance(float dt)
{
    m_elapsedSeconds += dt;
}

bool CParticleEmitter::IsEmitReady() const
{
    return m_elapsedSeconds > m_nextEmitTime;
}

std::unique_ptr<CDynamicParticle> CParticleEmitter::Emit()
{
    auto pParticle = std::make_unique<CDynamicParticle>();

    // Определяем время появления следующей частицы.
    m_elapsedSeconds -= m_nextEmitTime;
    m_nextEmitTime = m_emitIntervalRange(m_random);

    const float speed = m_speedRange(m_random);
    const float angle = m_angleRange(m_random);

    const glm::vec2 velocity = { speed * sinf(angle), speed * cosf(angle) };

	pParticle->SetLifetime(m_lifetimeRange(m_random));
	pParticle->SetVelocity(velocity);
	pParticle->SetPosition(m_position);

    return pParticle;
}

void CParticleEmitter::SetPosition(const glm::vec2 &value)
{
    m_position = value;
}

void CParticleEmitter::SetLifetimeRange(float minValue, float maxValue)
{
    m_lifetimeRange.param(minValue, maxValue);
}

void CParticleEmitter::SetRadiusRange(float minValue, float maxValue)
{
    m_radiusRange.param(linear_random_float::param_type(minValue, maxValue));
}

void CParticleEmitter::SetEmitIntervalRange(float minValue, float maxValue)
{
    m_emitIntervalRange.param(minValue, maxValue);
}

void CParticleEmitter::SetSpeedRange(float minValue, float maxValue)
{
    m_speedRange.param(minValue, maxValue);
}

void CParticleEmitter::SetAngleRange(float minValue, float maxValue)
{
    m_angleRange.param(minValue, maxValue);
}

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

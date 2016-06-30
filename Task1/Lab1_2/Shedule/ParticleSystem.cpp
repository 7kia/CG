#include "stdafx.h"
#include "ParticleSystem.h"

#include <limits>
#include <algorithm>

template<typename T>
bool IsBetween(T value, T min, T max)
{
	return (min <= value) && (value <= max);
}

CParticleSystem::CParticleSystem() = default;
CParticleSystem::~CParticleSystem() = default;

void CParticleSystem::SetEmitter(std::unique_ptr<CParticleEmitter> &&pEmitter)
{
    m_pEmitter = std::move(pEmitter);
}

void CParticleSystem::AddParticles(std::unique_ptr<CDynamicParticle> particle)
{
	m_particles.push_back(std::move(particle));
}

void CParticleSystem::Advance(float dt)
{
    // За 1 кадр может появиться несколько новых частиц.
    while (m_particles.size() < m_maxAmountParticles)
    {
        m_particles.emplace_back(m_pEmitter->Emit());
    }
    // Продвигаем частицы
    for (const auto &pParticle : m_particles)
    {
        pParticle->Advance(dt, GRAVITY);
    }

	do
	{
		auto newEnd = std::remove_if(m_particles.begin(), m_particles.end(), [&](const auto &pParticle) {
			return CheckExitFromBorder(pParticle->GetAbsolutePosition(pParticle->GetOrigin()));
		});

		/////////////////////////////////
		// Если перетаскиваемая частица выходит зв границы очищаем указатель на неё
		if (newEnd != m_particles.end())
		{
			if (m_draggingParticle == newEnd->get())
			{
				m_draggingParticle = nullptr;
			}

		}
		else
		{
			break;
		}

		/////////////////////////////////
		m_particles.erase(newEnd, m_particles.end());
	} while (true);
    // Удаляем вышедшие за экран частицы
   
}

void CParticleSystem::Draw() const
{
    for (const auto &pParticle : m_particles)
    {
        pParticle->Draw();
    }
}

void CParticleSystem::Redraw() const
{
	for (const auto & particle : m_particles)
	{
		particle->Redraw();
	}
}

void CParticleSystem::SetPosition(const glm::vec2 & position)
{
	m_pEmitter->SetPosition(position);

	for (auto & particle : m_particles)
	{
		particle->SetOrigin(position);
	}
}

void CParticleSystem::SetMaxAmountParticles(size_t amount)
{
	m_maxAmountParticles = amount;
}

size_t CParticleSystem::GetMaxAmountParticles()
{
	return m_maxAmountParticles;
}

bool CParticleSystem::CheckExitFromBorder(const glm::vec2 & particlePosition)
{
	glm::vec2 sizeWindow = m_pEmitter->GetPlaceSize();
	return !( IsBetween(particlePosition.x, 0.f, sizeWindow.x) 
			  && IsBetween(particlePosition.y, 0.f, sizeWindow.y) );
}

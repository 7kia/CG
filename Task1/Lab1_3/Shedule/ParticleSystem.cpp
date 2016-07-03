#include "stdafx.h"
#include "ParticleSystem.h"

#include <limits>
#include <algorithm>

template<typename T>
bool IsBetween(T value, T min, T max)
{
	return (min <= value) && (value <= max);
}

CPhysicalSystem::CPhysicalSystem() = default;
CPhysicalSystem::~CPhysicalSystem() = default;

void CPhysicalSystem::AddParticles(std::unique_ptr<CDynamicParticle> particle)
{
	m_particles.push_back(std::move(particle));
}

void CPhysicalSystem::Advance(float dt)
{
	ProcessCollisions();


	// TODO : gun add balls
    // За 1 кадр может появиться несколько новых частиц.
    //while (m_particles.size() < m_maxAmountParticles)
    //{
        //m_particles.emplace_back(m_pEmitter->Emit());
    //}
    // Продвигаем частицы
    for (const auto &pParticle : m_particles)
    {
        pParticle->Advance(dt);
    }

	do
	{
		auto newEnd = std::remove_if(m_particles.begin(), m_particles.end(), [&](const auto &pParticle) {
			return CheckExitFromBorder(pParticle->GetCenterPosition(pParticle->GetOrigin()));
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

void CPhysicalSystem::Draw() const
{
    for (const auto &pParticle : m_particles)
    {
        pParticle->Draw();
    }
}

void CPhysicalSystem::Redraw() const
{
	for (const auto & particle : m_particles)
	{
		particle->Redraw();
	}
}

void CPhysicalSystem::SetPosition(const glm::vec2 & position)
{
	for (auto & particle : m_particles)
	{
		particle->SetOrigin(position);
	}
}

void CPhysicalSystem::SetPlaceSize(const glm::vec2 & value)
{
	m_placeSize = value;
}

glm::vec2 CPhysicalSystem::GetPlaceSize() const
{
	return m_placeSize;
}

void CPhysicalSystem::ProcessCollisions()
{
	// TODO : rewrite	
}

void CPhysicalSystem::SetMaxAmountParticles(size_t amount)
{
	m_maxAmountParticles = amount;
}

size_t CPhysicalSystem::GetMaxAmountParticles()
{
	return m_maxAmountParticles;
}

bool CPhysicalSystem::CheckExitFromBorder(const glm::vec2 & particlePosition)
{
	glm::vec2 sizeWindow = GetPlaceSize();
	return !( IsBetween(particlePosition.x, 0.f, sizeWindow.x) 
			  && IsBetween(particlePosition.y, 0.f, sizeWindow.y) );
}

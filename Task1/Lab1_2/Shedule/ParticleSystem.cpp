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
	ProcessCollisions();


    // За 1 кадр может появиться несколько новых частиц.
    while (m_particles.size() < m_maxAmountParticles)
    {
        m_particles.emplace_back(m_pEmitter->Emit());
    }
    // Продвигаем частицы
    for (const auto &pParticle : m_particles)
    {
        pParticle->Advance(dt);
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

void CParticleSystem::ProcessCollisions()
{
	for (auto & firstParticle : m_particles)
	{
		for (auto & secondParticle : m_particles)
		{
			if (firstParticle != secondParticle)
			{
				bool firstSign = firstParticle->GetSign();
				bool secondSign = secondParticle->GetSign();

				const glm::vec2 power = GetPower(firstParticle, secondParticle);


				glm::vec2 vectorDistance = firstParticle->GetPosition() - secondParticle->GetPosition();
				float distance = glm::length(vectorDistance);

				if ( (distance < MIN_DISTANCE)
					&& 
					(glm::length(power) > MIN_POWER_FOR_INTERACTION) )
				{
					glm::vec2 firstAcceleration = GetAccelerationParticle(firstSign, power);
					glm::vec2 secondAcceleration = GetAccelerationParticle(secondSign, power);

					// very near particles repel
					// and particles with diferint attraction
					if ((distance < (DEFAULT_PARTICLE::RADIUSE * 2.f))
						|| (firstSign == secondSign))
					{
						secondAcceleration *= -1.f;
						firstAcceleration *= 1.f;

						
					}
					else if(firstSign != secondSign)
					{
						secondAcceleration *= -1.f;
					}

					if ((firstSign != secondSign) 
						&& (distance < (DEFAULT_PARTICLE::RADIUSE * 2.f)) )
					{
						secondAcceleration *= -1.f;
						firstAcceleration *= -1.f;
					}

					vectorDistance = glm::normalize(vectorDistance);
					// TODO : See is correctly name SetVelocity
					// ApplyAcceleration
					// SetVelocity нет взаиодействия с нексолькими частицами
					firstParticle->ApplyAcceleration(firstAcceleration);
					secondParticle->ApplyAcceleration(secondAcceleration);

				}
			}
		}
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

glm::vec2 CParticleSystem::GetPower(std::unique_ptr<CDynamicParticle> & first
								, std::unique_ptr<CDynamicParticle> & second)
{
	bool firstSign = first->GetSign();
	bool secondSign = second->GetSign();

	float firstCharge = GetChargeParticle(firstSign);
	float secondCharge = GetChargeParticle(secondSign);


	// see might need absolute position
	glm::vec2 vectorDistance = first->GetAbsolutePosition(first->GetOrigin());
	vectorDistance -= second->GetAbsolutePosition(second->GetOrigin());

	float distance = glm::length(vectorDistance);
	if (distance < DEFAULT_PARTICLE::RADIUSE * 2.f)
	{
		distance = DEFAULT_PARTICLE::RADIUSE * 2.f;
	}
	const float power = K_IN_COULOMB_LAW * firstCharge * secondCharge
						/ pow(distance, 2.f);


	const glm::vec2 result = power * vectorDistance;
	return result;
}

float CParticleSystem::GetChargeParticle(bool sign)
{
	return (sign ? ELECTRON_CHARGE : PROTON_CHARGE);
}

glm::vec2 CParticleSystem::GetAccelerationParticle(bool sign, const glm::vec2 & power)
{
	return power / (sign ? ELECTRON_MASSA : PROTON_MASSA);
}

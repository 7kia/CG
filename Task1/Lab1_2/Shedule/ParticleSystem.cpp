#include "stdafx.h"
#include "ParticleSystem.h"

#include <limits>
#include <algorithm>

template<typename T>
bool IsBetween(T value, T min, T max)
{
	return (min <= value) && (value <= max);
}

CParticleSystem::CParticleSystem()
{
}


CParticleSystem::~CParticleSystem() = default;

void CParticleSystem::SetEmitter(std::unique_ptr<CParticleEmitter> &&pEmitter)
{
    m_pEmitter = std::move(pEmitter);
}

void CParticleSystem::AddParticles(std::shared_ptr<CStaticParticle> particle)
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
			return CheckExitFromBorder(pParticle->GetCenterPosition());
		});

		/////////////////////////////////
		// Если перетаскиваемая частица выходит зв границы очищаем указатель на неё
		if (newEnd != m_particles.end())
		{
			if (!m_draggingParticle.expired())
			{
				//if (Lock(m_draggingParticle).get() == newEnd->get())
				//{
					m_draggingParticle.reset();
				//}
			}
			

		}
		else
		{
			break;
		}
		/////////////////////////////////
		m_particles.erase(newEnd, m_particles.end());
	} while (true);   
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
				// TODO : 
				const glm::vec2 power = GetPower(firstParticle, secondParticle);

				glm::vec2 vectorDistance = firstParticle->GetPosition() - secondParticle->GetPosition();
				float distance = glm::length(vectorDistance);

				if ( (distance < MIN_DISTANCE)
					&& 
					(glm::length(power) > MIN_POWER_FOR_INTERACTION))
				{
					const bool firstSign = firstParticle->GetSign();
					const bool secondSign = secondParticle->GetSign();

					glm::vec2 firstAcceleration = GetParticleAcceleration(firstSign, power);
					glm::vec2 secondAcceleration = GetParticleAcceleration(secondSign, power);					

					if (distance < MIN_DISTANCE_BETWEEN_PARTICLE)
					{
						if (firstSign == secondSign)
						{
							secondAcceleration *= -5.f;
						}
						else
						{
							firstAcceleration *= -5.f;
						}
					}
					else
					{
						secondAcceleration *= -5.f;
						firstAcceleration *= 5.f;
					}

					vectorDistance = glm::normalize(vectorDistance);

					// For lack shake equal sign particle
					if (!((firstSign != secondSign)
							&&
						IsBetween(distance
									, MIN_DISTANCE_BETWEEN_PARTICLE - EPSILON_DISTANCE
									, MIN_DISTANCE_BETWEEN_PARTICLE + EPSILON_DISTANCE)))
					{
						firstParticle->ApplyAcceleration(firstAcceleration);
						secondParticle->ApplyAcceleration(secondAcceleration);
					}

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

glm::vec2 GetPower(std::shared_ptr<CStaticParticle> & first
								, std::shared_ptr<CStaticParticle> & second)
{
	const float firstCharge = GetParticleCharge(first->GetSign());
	const float secondCharge = GetParticleCharge(second->GetSign());

	// see might need absolute position
	const glm::vec2 distanceVector = first->GetCenterPosition() - second->GetCenterPosition();

	const float distance = glm::length(distanceVector);// , MIN_DISTANCE_BETWEEN_PARTICLE);

	auto getWeakImpactPower = [](float distance)
	{
		const float shift = -51.f;
		const float x = distance + shift;
		return (abs(x * 2) / (powf(x, 2.f) + x * 1.5f + 1)) * 200000.f;
	};
	auto getCoulombPower = [](float distance)
	{
		const float shift = -49.9f;
		const float x = distance + shift;
		return (1.f / (x * x)) * 100.f;
	};
	const float denumerator = (distance < MIN_DISTANCE_BETWEEN_PARTICLE) ? getWeakImpactPower(distance) : pow(distance, 3.f);//
	
	const float df = (distance < MIN_DISTANCE_BETWEEN_PARTICLE) ? getCoulombPower(distance) : pow(distance, 3.f);
	const float power = K_IN_COULOMB_LAW * firstCharge * secondCharge / denumerator;

	return power * glm::normalize(distanceVector);
}

float GetParticleCharge(bool sign)
{
	return (sign ? ELECTRON_CHARGE : PROTON_CHARGE);
}

glm::vec2 GetParticleAcceleration(bool sign, const glm::vec2 & power)
{
	return power / (sign ? ELECTRON_MASS : PROTON_MASS);
}

std::shared_ptr<CStaticParticle> Lock(std::weak_ptr<CStaticParticle> pointer)
{
	return pointer.lock();
}

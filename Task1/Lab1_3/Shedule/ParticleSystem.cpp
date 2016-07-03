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

void CPhysicalSystem::SetEmitter(std::unique_ptr<CParticleEmitter> &&pEmitter)
{
    m_pEmitter = std::move(pEmitter);
}

void CPhysicalSystem::AddParticles(std::unique_ptr<CDynamicParticle> particle)
{
	m_particles.push_back(std::move(particle));
}

void CPhysicalSystem::Advance(float dt)
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
	m_pEmitter->SetPosition(position);

	for (auto & particle : m_particles)
	{
		particle->SetOrigin(position);
	}
}

void CPhysicalSystem::ProcessCollisions()
{
	for (auto & firstParticle : m_particles)
	{
		for (auto & secondParticle : m_particles)
		{
			if (firstParticle != secondParticle)
			{
				bool firstSign = firstParticle->IsNegativeCharge();
				bool secondSign = secondParticle->IsNegativeCharge();

				float power = GetPower(*firstParticle, *secondParticle);


				glm::vec2 vectorDistance = firstParticle->GetPosition() - secondParticle->GetPosition();
				float distance = glm::length(vectorDistance);

				if ((power != std::numeric_limits<float>::infinity())
					&& (power > MIN_POWER_FOR_INTERACTION))
				{
					float firstAcceleration = GetAccelerationParticle(firstSign, power);
					float secondAcceleration = GetAccelerationParticle(secondSign, power);

					// very near particles repel
					// and particles with diferint attraction
					if ( (distance < (DEFAULT_PARTICLE::RADIUSE * 2.f))
						|| (firstSign == secondSign))
					{
						secondAcceleration *= -2.f;
						firstAcceleration *= 2.f;
					}
					else
					{
						firstAcceleration *= -1.f;
					}

					vectorDistance = glm::normalize(vectorDistance);
					// TODO : See is correctly name SetVelocity
					// ApplyAcceleration
					// SetVelocity нет взаиодействия с нексолькими частицами
					firstParticle->ApplyAcceleration(vectorDistance * firstAcceleration);
					secondParticle->ApplyAcceleration(vectorDistance * secondAcceleration);

				}
			}
		}
	}
		
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
	glm::vec2 sizeWindow = m_pEmitter->GetPlaceSize();
	return !( IsBetween(particlePosition.x, 0.f, sizeWindow.x) 
			  && IsBetween(particlePosition.y, 0.f, sizeWindow.y) );
}

float CPhysicalSystem::GetPower(CDynamicParticle & first, CDynamicParticle & second)
{
	const bool firstSign = first.IsNegativeCharge();
	const bool secondSign = second.IsNegativeCharge();

	const float firstCharge = GetParticleCharge(firstSign);
	const float secondCharge = GetParticleCharge(secondSign);

	const float intristicPower = K_IN_COULOMB_LAW * firstCharge * secondCharge;

	// see might need absolute position
	// TODO : fix GetCenterPosition
	const glm::vec2 vectorDistance = first.GetCenterPosition(first.GetOrigin()) - second.GetCenterPosition(second.GetOrigin());

	const float distance = glm::length(vectorDistance);
	// TODO : fix coefficients
	const float power = abs(intristicPower / (distance));// ; * distance

	return power;
}

float CPhysicalSystem::GetParticleCharge(bool sign)
{
	// заряд одного элекстрона 1.60217662 * 10e-19
	// для расчётов слишком маленькое число
	return sign ? -1.f : 1.f;
}

float CPhysicalSystem::GetAccelerationParticle(bool sign, float power)
{
	float mass = sign ? ELECTRON_MASS : PROTON_MASS;

	return power / mass;
}

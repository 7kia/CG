#include "stdafx.h"
#include "PhysicalSystem.h"

#include <limits>
#include <algorithm>

template<typename T>
bool IsBetween(T value, T min, T max)
{
	return (min <= value) && (value <= max);
}

CPhysicalSystem::CPhysicalSystem() = default;
CPhysicalSystem::~CPhysicalSystem() = default;

void CPhysicalSystem::AddShape(std::shared_ptr<CStaticShape> particle)
{
	m_shapes.push_back(std::move(particle));
}

void CPhysicalSystem::Advance(float dt)
{
	ProcessCollisions();


	// TODO : gun add balls
    // За 1 кадр может появиться несколько новых частиц.
    while (m_shapes.size() < m_maxAmountBalls)
    {
       m_shapes.emplace_back(std::make_shared<CBall>());
    }

	// TODO : rewrite
    // Продвигаем частицы
    for (const auto &pShape : m_shapes)
    {
       // pShape->Advance(dt);
    }

	do
	{
		auto newEnd = std::remove_if(m_shapes.begin(), m_shapes.end(), [&](const auto &pShape) {
			return CheckExitFromBorder(pShape->GetCenterPosition(pShape->GetOrigin()));
		});

		/////////////////////////////////
		// Если перетаскиваемая частица выходит зв границы очищаем указатель на неё
		if (newEnd != m_shapes.end())
		{
			if (m_draggingShape == newEnd->get())
			{
				m_draggingShape = nullptr;
			}

		}
		else
		{
			break;
		}

		/////////////////////////////////
		m_shapes.erase(newEnd, m_shapes.end());
	} while (true);
    // Удаляем вышедшие за экран частицы
   
}

void CPhysicalSystem::Draw() const
{
    for (const auto &pShape : m_shapes)
    {
        pShape->Draw();
    }
}

void CPhysicalSystem::Redraw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Redraw();
	}
}

void CPhysicalSystem::SetPosition(const glm::vec2 & position)
{
	for (auto & shape : m_shapes)
	{
		shape->SetOrigin(position);
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

void CPhysicalSystem::SetMaxAmountBalls(size_t amount)
{
	m_maxAmountBalls = amount;
}

size_t CPhysicalSystem::GetMaxAmountBalls()
{
	return m_maxAmountBalls;
}

bool CPhysicalSystem::CheckExitFromBorder(const glm::vec2 & particlePosition)
{
	glm::vec2 sizeWindow = GetPlaceSize();
	return !( IsBetween(particlePosition.x, 0.f, sizeWindow.x) 
			  && IsBetween(particlePosition.y, 0.f, sizeWindow.y) );
}

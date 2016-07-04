#include "stdafx.h"
#include "PhysicalSystem.h"

#include <limits>
#include <algorithm>

static float BORDER_WIDTH = 50.f;
static float BORDER_HEIGTH = 500.f;
static float SIDE_SHIFT = 400.f;


template<typename T>
bool IsBetween(T value, T min, T max)
{
	return (min <= value) && (value <= max);
}

CPhysicalSystem::CPhysicalSystem()
{
	//////////////////////////
	// Left wall
	glm::vec2 position = glm::vec2(-350.f, -BORDER_HEIGTH / 2.f);
	float width = BORDER_WIDTH;
	float height = BORDER_HEIGTH;
	glm::vec3 color = Colors::RED;
	float rotation = 0.f;

	CreateWall(position
				, width
				, height
				, rotation
				, color);
	//////////////////////////
	// Right wall
	position = glm::vec2(300.f, -BORDER_HEIGTH / 2.f );
	width = BORDER_WIDTH;
	height = BORDER_HEIGTH;
	color = Colors::RED;
	rotation = 0.f;

	CreateWall(position
		, width
		, height
		, rotation
		, color);
	//////////////////////////

	//////////////////////////
	// Top wall
	position = glm::vec2(-350.f, -BORDER_HEIGTH / 2.f - BORDER_WIDTH);
	width = BORDER_HEIGTH + 4.f * BORDER_WIDTH;
	height = BORDER_WIDTH;
	color = Colors::ORANGE;
	rotation = 0.f;

	CreateWall(position
		, width
		, height
		, rotation
		, color);
	//////////////////////////
	// Left low wall
	position = glm::vec2(-300.f, 50.f);
	width = 500.f;
	height = BORDER_WIDTH / 2.f;
	color = Colors::RED;
	rotation = 0.4f;

	CreateWall(position
		, width
		, height
		, rotation
		, color);
	//////////////////////////
	// Right low wall
	position = glm::vec2(325.f, 50.f);
	width = 300.f;
	height = BORDER_WIDTH / 2.f;
	color = Colors::RED;
	rotation = 2.97f;

	CreateWall(position
		, width
		, height
		, rotation
		, color);
	//////////////////////////
	// Rectangle wall
	position = glm::vec2(-100.f, -150.f);
	width = 50.f;
	height = 100.f;
	color = Colors::RED;
	rotation = 1.1f;

	CreateWall(position
		, width
		, height
		, rotation
		, color);
	//////////////////////////
	// Gun

	auto pGun = std::make_shared<CGun>();
	m_shapes.push_back(std::move(pGun));

}

CPhysicalSystem::~CPhysicalSystem() = default;


void CPhysicalSystem::CreateWall(const glm::vec2 & leftTopPoint
	, float width
	, float height
	, float rotation
	, const glm::vec3 & color)
{
	auto pRectangle = std::make_shared<CRectangle>();

	pRectangle->SetHeight(height);
	pRectangle->SetWidth(width);
	pRectangle->SetOutlineColor(color);
	pRectangle->SetPosition(leftTopPoint);
	pRectangle->SetRotation(rotation);

	AddShape(pRectangle);
}

void CPhysicalSystem::AddShape(std::shared_ptr<CStaticShape> particle)
{
	m_shapes.push_back(std::move(particle));
}

void CPhysicalSystem::Advance(float dt)
{
	ProcessCollisions();
	SetPosition(m_placeSize / 2.f);

	// TODO : gun add balls
    // За 1 кадр может появиться несколько новых частиц.
    //while (m_shapes.size() < m_maxAmountBalls)
    //{
    //   m_shapes.emplace_back(std::make_shared<CBall>());
    //}

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

	m_position = position;
}

glm::vec2 CPhysicalSystem::GetPosition() const
{
	return m_position;
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

void CGun::Shoot(CPhysicalSystem * system, const glm::vec2 & direction)
{
	auto pBall = std::make_shared<CBall>();

	pBall->SetOrigin(system->GetPosition());
	pBall->SetOutlineColor(Colors::YELLOW);
	pBall->SetPosition(GetPosition() + DEFAULT_GUN::SHIFT_BALL * direction);
	

	system->AddShape(pBall);
}
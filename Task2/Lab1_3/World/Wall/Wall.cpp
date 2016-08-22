#include "stdafx.h"
#include "Wall.h"

CWall::CWall()
	: IActor()
	, ITransformable()
	, IHave3DPosition()
	, IHavePointerToWallViewType()
	, IHaveVisiblePart()
{
}

void CWall::Draw() const
{
	m_visual.Draw();
}

void CWall::Update(float deltaTime)
{
	if (m_haveCollision)
	{
		m_collision->Advance(deltaTime);
	}
}

void CWall::SetType(const CWallViewType * type)
{
	m_visual.SetType(type);
}

const CWallViewType * CWall::GetType() const
{
	return m_visual.GetType();
}

void CWall::SetVisible(size_t index, bool value)
{
	CheckVisibleIndex(index);

	m_visual.SetVisible(index, value);
}

bool CWall::GetVisible(size_t index) const
{
	CheckVisibleIndex(index);
	return m_visual.GetVisible(index);
}

void CWall::SetVisible(bool value)
{
	m_visual.SetVisible(value);
}

void CWall::CheckVisibleIndex(size_t index) const
{
	(void)index;
	// TODO : rewrite the method
}

void CWall::SetPosition(const glm::vec3 & value)
{
	m_visual.SetTransform(glm::translate(glm::mat4(), value));

	if (m_haveCollision)
	{
		m_collision->SetPosition(value.x, value.z);// z coordinate not important, z instead y 
	}
}

glm::vec3 CWall::GetPosition() const
{
	const glm::mat4 transform = m_visual.GetTransform();
	return glm::vec3(transform[3][0], transform[3][1], transform[3][2]);
}

void CWall::Move(const glm::vec3 & value)
{
	SetPosition(GetPosition() + value);
}

void CWall::SetTransform(const glm::mat4 & transform)
{
	m_visual.SetTransform(transform);	

	if (m_haveCollision)
	{
		m_collision->SetPosition(transform[3][0], transform[3][2]);
	}
}

glm::mat4 CWall::GetTransform() const
{
	return m_visual.GetTransform();
}

void CWall::AddToWorld(b2World * world)
{
	if (CheckContentCollision())
	{
		m_collision->SetWidth(WallSpace::SIZE);
		m_collision->SetHeight(WallSpace::SIZE);
		m_collision->AddToWorld(world);
	}
}

void CWall::SetHaveCollision(bool value)
{
	m_haveCollision = value;
	if (value)
	{
		m_collision = std::make_shared<C2DRectangleCollision>();
		m_collision->SetPVisual(&m_visual);
	}
}

bool CWall::GetHaveCollision() const
{
	return m_haveCollision;
}

const CWallView * CWall::GetVisual() const
{
	return &m_visual;
}

bool CWall::CheckContentCollision() const
{
	if (m_haveCollision)
	{
		return true;
	}
	throw std::runtime_error("The wall not have collision");
}

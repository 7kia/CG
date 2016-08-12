#include "stdafx.h"
#include "../../stdafx.h"
#include "Wall.h"

CWall::CWall()
	: IActor()
	, ITransformable()
	, IHave3DPosition()
	, IHavePointerToWallViewType()
	, IHaveVisiblePart()
	, m_collision(&m_visual)
{
	m_collision.SetWidth(WallSpace::SIZE);
	m_collision.SetHeight(WallSpace::SIZE);
}

void CWall::Draw() const
{
	m_visual.Draw();
}

void CWall::Update(float deltaTime)
{
	m_collision.Advance(deltaTime);
}

void CWall::SetType(const CWallViewType * type)
{
	m_visual.SetType(type);
}

const CWallViewType * CWall::GetType() const
{
	return m_visual.GetType();
}

void CWall::SetVisible(unsigned index, bool value)
{
	CheckVisibleIndex(index);

	m_visual.SetVisible(index, value);
}

bool CWall::GetVisible(unsigned index) const
{
	CheckVisibleIndex(index);
	return m_visual.GetVisible(index);
}

void CWall::CheckVisibleIndex(unsigned index) const
{
	(void)index;
	// TODO : rewrite the method
}

void CWall::SetPosition(const glm::vec3 & value)
{
	m_visual.SetTransform(glm::translate(glm::mat4(), value));
	m_collision.SetPosition(value.x, value.z);// z coordinate not important, z instead y 
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
	m_collision.SetPosition(transform[3][0], transform[3][2]);
}

glm::mat4 CWall::GetTransform() const
{
	return m_visual.GetTransform();
}

void CWall::AddToWorld(b2World * world)
{
	m_collision.AddToWorld(world);
}

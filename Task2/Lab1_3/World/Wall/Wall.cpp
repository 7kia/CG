#include "Wall.h"

CWall::CWall()
	: IActor()
{
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

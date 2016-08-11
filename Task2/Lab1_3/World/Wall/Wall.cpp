#include "stdafx.h"
#include "../../stdafx.h"
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

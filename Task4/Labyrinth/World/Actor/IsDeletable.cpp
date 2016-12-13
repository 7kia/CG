#include "stdafx.h"
#include "IsDeletable.h"

CIsDeletable::CIsDeletable()
{
}

void CIsDeletable::SetStateLive(bool state)
{
	m_isLive = state;
}

bool CIsDeletable::IsLive() const
{
	return m_isLive;
}

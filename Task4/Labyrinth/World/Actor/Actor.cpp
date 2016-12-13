#include "stdafx.h"
#include "Actor.h"

IActor::IActor(idClass id)
{
	m_idClass = id;
}

IActor::idClass IActor::GetIdClass() const
{
	return m_idClass;
}

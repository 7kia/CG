#include "stdafx.h"
#include "Actor.h"

CActor::CActor(idClass id)
	: IDrawable()
	, IUpdatable()
	, CIsDeletable()

{
	m_idClass = id;
}

CActor::idClass CActor::GetIdClass() const
{
	return m_idClass;
}

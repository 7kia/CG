#include "stdafx.h"
#include "Actor.h"

CActor::CActor(IdClass id)
	: IDrawable()
	, IUpdatable()
	, CIsDeletable()
	, CHaveFaction()

{
	m_idClass = id;
}

CActor::IdClass CActor::GetIdClass() const
{
	return m_idClass;
}

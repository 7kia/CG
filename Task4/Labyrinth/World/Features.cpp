#include "stdafx.h"
#include "Features.h"

void CDynamicFeature::SetValue(int setValue)
{
	m_value = setValue;
}

void CDynamicFeature::AddToValue(int summand)
{
	m_value += summand;
}

int CDynamicFeature::GetValue() const
{
	return m_value;
}

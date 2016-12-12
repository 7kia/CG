#include "stdafx.h"
#include "Features.h"


void CStaticFeature::SetValue(int setValue)
{
	m_value = setValue;
}

void CStaticFeature::AddToValue(int summand)
{
	m_value += summand;
}

int CStaticFeature::GetValue() const
{
	return m_value;
}


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

void CDynamicFeature::SetMaxValue(int setValue)
{
	m_maxValue = setValue;
}

void CDynamicFeature::AddMaxToValue(int summand)
{
	m_maxValue += summand;
}

int	CDynamicFeature::GetMaxValue() const
{
	return m_maxValue;
}


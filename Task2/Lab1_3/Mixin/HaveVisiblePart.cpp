#include "stdafx.h"
#include "HaveVisiblePart.h"

CHaveVisiblePart::CHaveVisiblePart(size_t size)
	: m_visible(size, true)
{
}

void CHaveVisiblePart::SetVisible(unsigned index, bool value)
{
	CheckVisibleIndex(index);

	m_visible[index] = value;
}

bool CHaveVisiblePart::GetVisible(unsigned index) const
{
	CheckVisibleIndex(index);

	return m_visible[index];
}

void CHaveVisiblePart::CheckVisibleIndex(unsigned index) const
{
	if (!IsBetween(index, 0u, unsigned(m_visible.size())))
	{
		throw std::runtime_error("Wall have not the index");
	}
}

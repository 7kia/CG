#include "stdafx.h"
#include "HaveVisiblePart.h"

CHaveVisiblePart::CHaveVisiblePart(size_t size)
	: m_visible(size)
{
}

void CHaveVisiblePart::SetVisible(uint index, bool value)
{
	CheckVisibleIndex(index);

	m_visible[index] = value;
}

bool CHaveVisiblePart::GetVisible(uint index) const
{
	CheckVisibleIndex(index);

	return m_visible[index];
}

void CHaveVisiblePart::CheckVisibleIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_visible.size())))
	{
		throw std::runtime_error("Wall have not the index");
	}
}

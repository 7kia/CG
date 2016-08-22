#include "stdafx.h"
#include "HaveVisiblePart.h"

CHaveVisiblePart::CHaveVisiblePart(size_t size)
	: m_visible(size, true)
{
}

void CHaveVisiblePart::SetVisible(bool value)
{
	for (auto & element : m_visible)
	{
		element = value;
	}
}

void CHaveVisiblePart::SetVisible(size_t index, bool value)
{
	CheckVisibleIndex(index);

	m_visible[index] = value;
}

bool CHaveVisiblePart::GetVisible(size_t index) const
{
	CheckVisibleIndex(index);

	return m_visible[index];
}

void CHaveVisiblePart::CheckVisibleIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_visible.size()))
	{
		throw std::runtime_error("Wall have not the index");
	}
}

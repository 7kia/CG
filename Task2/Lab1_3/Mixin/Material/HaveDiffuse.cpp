#include "stdafx.h"
#include "HaveDiffuse.h"

CHaveDiffuse::CHaveDiffuse()
	: IHaveDiffuse()
{
}

void CHaveDiffuse::SetDiffuse(const glm::vec4 & diffuse)
{
	m_diffuse = diffuse;
}

glm::vec4 CHaveDiffuse::GetDiffuse() const
{
	return m_diffuse;
}

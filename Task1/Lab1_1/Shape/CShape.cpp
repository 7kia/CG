#include "stdafx.h"
#include "CShape.h"

CShape::~CShape()
{
}

void CShape::SetOutlineColor(const glm::vec3 & color)
{
	m_outlineColor = color;
}

glm::vec3 CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

CDrawable::~CDrawable()
{
}

void CDrawable::Draw() const
{
	// если дисплейный список еще не был создан, то для начала создаем его
	if (!m_displayList)
	{
		// Генерируем новый дисплейный список для цветка
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);
		// Для заполнения списка вызываем redraw.
		Redraw();
		// завершаем дисплейный список
		glEndList();
	}

	// вызываем ранее созданный дисплейный список
	glCallList(m_displayList);
}

void CDrawable::DeleteList()
{
	if (m_displayList)
	{
		glDeleteLists(m_displayList, 1);
		m_displayList = 0;
	}
}

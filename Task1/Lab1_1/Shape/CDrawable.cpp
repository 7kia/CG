#include "stdafx.h"
#include "CDrawable.h"

CDrawable::~CDrawable()
{
}

void CDrawable::Draw() const
{
	// ���� ���������� ������ ��� �� ��� ������, �� ��� ������ ������� ���
	if (!m_displayList)
	{
		// ���������� ����� ���������� ������ ��� ������
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);
		// ��� ���������� ������ �������� redraw.
		Redraw();
		// ��������� ���������� ������
		glEndList();
	}

	// �������� ����� ��������� ���������� ������
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


#pragma once

class CRotatable
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	float		GetRotation() const;
	void		SetRotation(float rotation);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	float		m_rotation = 0.f;
//////////////////////////////////////////////////////////////////////

};
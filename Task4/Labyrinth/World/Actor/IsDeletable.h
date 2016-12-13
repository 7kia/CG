#pragma once


class CIsDeletable
{
public:
	CIsDeletable();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void				SetStateLive(bool state);

	bool				IsLive() const;
protected:
	bool				m_isLive = true;
};
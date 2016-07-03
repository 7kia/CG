#include "IDrawable.h"

//////////////////////////////////////////
// CDrawable - consist Draw(), data about creation
//////////////////////////////////////////
class CDrawable
	: public IDrawable
{
public:
	CDrawable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					Draw() const;
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void					DeleteList();
//////////////////////////////////////////////////////////////////////
// Data
private:
	mutable unsigned		m_displayList = 0;
//////////////////////////////////////////////////////////////////////
};

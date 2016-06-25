#include "IDrawable.h"

//////////////////////////////////////////
// CDrawable - consist Draw(), data about creation
//////////////////////////////////////////
class CDrawable
	: public IDrawable
{
public:
	CDrawable() = default;
	virtual ~CDrawable();
public:

	void					Draw() const;

protected:// TODO : if need replace on private
	void					DeleteList();
	mutable unsigned		m_displayList = 0;

};
#pragma once

#include "Minus.h"

static const glm::vec3 POSITIVE_COLOR = { 1.f, 0.f, 0.f };


class CPlus final
	: public CMinus
{
public:
	CPlus();
	CPlus(const glm::vec2 & position);
	virtual ~CPlus() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
};
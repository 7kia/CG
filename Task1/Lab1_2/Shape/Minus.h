#pragma once

#include "stdafx.h"

#include "CShape.h"
#include "CHavePosition.h"

static const glm::vec3 NEGATIVE_COLOR = { 0.f, 0.f, 1.f };

static const float WIDTH_SIGN = 5.f;
static const float HEIGHT_SIGN = 25.f;


class CMinus final// was exported from third lab by OOP
	: public CShape
	, public CHavePosition
	, private boost::noncopyable

{
public:
	CMinus();
	CMinus(const glm::vec2 & position);
	~CMinus();

public:
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//
private:
};
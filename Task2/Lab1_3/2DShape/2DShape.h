#pragma once

#include "I2DShape.h"
#include "../2DMixins/CHave2DPosition.h"
#include "../2DMixins/CHave2DOrigin.h"
#include "../2DMixins/C2DRotatable.h"

static const float SCALE_FACTOR = 25.f;

struct SIntRect
{
	float x;
	float y;
	float width;
	float height;
};

//////////////////////////////////////////
// CShape - basic for everything shapes, consist common data
//////////////////////////////////////////
class CShape
	: public I2DShape
	, public CHavePositionAndOrigin
	, public C2DRotatable

{
public:
	CShape();
	virtual ~CShape() = default;

//////////////////////////////////////////////////////////////////////
// Methods
public:
//////////////////////////////////////////////////////////////////////
// Data
public:
//////////////////////////////////////////////////////////////////////
// Methods
protected:
//////////////////////////////////////////////////////////////////////
// Data
protected:
//////////////////////////////////////////////////////////////////////

};
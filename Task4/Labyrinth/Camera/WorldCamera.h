#pragma once

#include "Camera.h"

class CWorldCamera
	: public CAbstractRotatableCamera
	, private boost::noncopyable
{
public:
	explicit CWorldCamera(float rotationRadians, float distance);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		Update(float deltaSec
						, float moveSpeed
						, float rotationSpeed) override;

	glm::mat4	GetViewTransform() const override;
//////////////////////////////////////////////////////////////////////
// Data
private:
	float		m_distance = 1;
};

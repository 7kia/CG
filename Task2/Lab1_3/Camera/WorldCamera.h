#pragma once

#include "Camera.h"

// TODO : rename
class CWorldCamera
	: public CAbcstartCamera
	, private boost::noncopyable
{
public:
	explicit CWorldCamera(float rotationRadians, float distance);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	// IUpdatable
	void Update(float deltaSec) override;
	//--------------------------------------------
	// IInputEventAcceptor
	glm::mat4 GetViewTransform() const override;
	//--------------------------------------------
private:
	float m_rotationRadians = 0;
	float m_distance = 1;
};

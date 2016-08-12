#pragma once

#include "Camera.h"

// TODO : rename
class CWorldCamera
	: public CAbstractRotatableCamera
	, private boost::noncopyable
{
public:
	//CWorldCamera() = default;
	explicit CWorldCamera(float rotationRadians, float distance);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IUpdatable
	void Update(float deltaSec
				, float moveSpeed
				, float rotationSpeed) override;
	//--------------------------------------------
	// IInputEventAcceptor
	glm::mat4 GetViewTransform() const override;
	//--------------------------------------------
private:
	float m_distance = 1;
};

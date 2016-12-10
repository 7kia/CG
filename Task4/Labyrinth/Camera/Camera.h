#pragma once

#include <glm/fwd.hpp>
#include <SDL2/SDL_events.h>
#include <boost/noncopyable.hpp>
#include <set>
#include <glm/gtx/rotate_vector.hpp>


#include "../Mixin/Updatable.h"
#include "../Mixin/Have3DPosition.h"
#include "../Mixin/HaveDirection.h"

class CAbcstartCamera
	: public CHave3DPosition
	, public CHaveDirection
{
public:
	CAbcstartCamera();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// TODO
	// Need coordinate with IInputEventAcceptor
	// two low methods is common for all cameras
	virtual				glm::mat4 GetViewTransform() const = 0;

	virtual void Update(float deltaSec
						, float moveSpeed
						, float rotationSpeed) = 0;

//////////////////////////////////////////////////////////////////////
// Data
protected:

};

class CAbstractRotatableCamera
	: public CAbcstartCamera
{
public:
	CAbstractRotatableCamera() = default;
	CAbstractRotatableCamera(float rotationRadians);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	float		GetRotationRadians() const;
	glm::vec3	GetCurrentDirection() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	float		m_rotationRadians = 0;
};
#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <boost/noncopyable.hpp>
#include <set>

#include "Mixin/Material/MaterialCharacteristics.h"

#include "Mixin\HaveDirection.h"
#include "Mixin\Have3DPosition.h"
#include "Mixin\Drawable.h"
#include "3DShape\3DSphere.h"

class ILightSource
{
public:
    virtual ~ILightSource() = default;
    virtual void Setup() const = 0;
	virtual void Disable() const {};

};

class CAbstractLightSource
        : public ILightSource
		, public IDrawable
		, public CMaterialCharactiristics
        , private boost::noncopyable
{
public:
    /// @param index - один из GL_LIGHT*
    CAbstractLightSource(unsigned index);
//////////////////////////////////////////////////////////////////////
// Methods
protected:
    void		SetupImpl() const;
    unsigned	GetIndex() const;

	void		Draw() const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
    unsigned			m_index;
	CIdentity3DSphere	m_visual;
};

class CDirectedLightSource 
	: public CAbstractLightSource
	, public CHaveDirection
{
public:
    /// @param index - один из GL_LIGHT*
    CDirectedLightSource(unsigned index);
//////////////////////////////////////////////////////////////////////
// Methods
public:
    void Setup() const override;
};

class CPositionLightSource 
	: public CAbstractLightSource
	, public CHave3DPosition
{
public:
    /// @param index - один из GL_LIGHT*
    CPositionLightSource(unsigned index);
//////////////////////////////////////////////////////////////////////
// Methods
public:
    void Setup() const override;
	void Disable() const override;

	void Draw() const override;

};

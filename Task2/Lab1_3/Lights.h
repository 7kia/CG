#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <boost/noncopyable.hpp>
#include <set>

#include "Mixin/Material/MaterialCharacteristics.h"

#include "Mixin\HaveDirection.h"
#include "Mixin\Have3DPosition.h"

class ILightSource
{
public:
    virtual ~ILightSource() = default;
    virtual void Setup()const = 0;
};

class CAbstractLightSource
        : public ILightSource
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
//////////////////////////////////////////////////////////////////////
// Data
private:
    unsigned	m_index;
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
};

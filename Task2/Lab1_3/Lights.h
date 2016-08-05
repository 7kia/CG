#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <boost/noncopyable.hpp>
#include <set>

#include "Mixin\Material\HaveAmbient.h"
#include "Mixin\Material\HaveDiffuse.h"
#include "Mixin\Material\HaveSpecular.h"
#include "Mixin\Material\HaveEmission.h"
#include "Mixin\Material\HaveShininess.h"

#include "Mixin\HaveDirection.h"
#include "Mixin\HavePosition.h"

class ILightSource
{
public:
    virtual ~ILightSource() = default;
    virtual void Setup()const = 0;
};

class CAbstractLightSource
        : public ILightSource
		, public CHaveAmbient
		, public CHaveDiffuse
		, public CHaveSpecular
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
	, public CHavePosition
{
public:
    /// @param index - один из GL_LIGHT*
    CPositionLightSource(unsigned index);
//////////////////////////////////////////////////////////////////////
// Methods
public:
    void Setup() const override;
};

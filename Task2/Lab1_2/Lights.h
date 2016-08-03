#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <boost/noncopyable.hpp>
#include <set>

#include "Mixin\Material\HaveAmbient.h"
#include "Mixin\Material\HaveDiffuse.h"
#include "Mixin\Material\HaveSpecular.h"
#include "Mixin\HaveDirection.h"

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

class CPositionLightSource : public CAbstractLightSource
{
public:
    /// @param index - один из GL_LIGHT*
    CPositionLightSource(unsigned index);

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3 &value);

    void Setup() const override;

private:
    glm::vec4 m_position;
};

class CPhongModelMaterial
{
public:
    void Setup() const;

    glm::vec4 GetEmission() const;
    glm::vec4 GetAmbient() const;
    glm::vec4 GetDiffuse() const;
    glm::vec4 GetSpecular() const;
    float GetShininess() const;

    void SetAmbient(const glm::vec4 &GetAmbient);
    void SetEmission(const glm::vec4 &GetEmission);
    void SetDiffuse(const glm::vec4 &GetDiffuse);
    void SetSpecular(const glm::vec4 &GetSpecular);
    void SetShininess(float GetShininess);

private:
    glm::vec4 m_emission;
    glm::vec4 m_ambient;
    glm::vec4 m_diffuse;
    glm::vec4 m_specular;
    float m_shininess = 10.f;
};

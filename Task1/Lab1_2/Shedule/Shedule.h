#pragma once

#pragma once

#include "../Shape/Particle.h"
#include "ParticleSystem.h"

#include <memory>
#include <vector>

static const float DIVISION_WIDTH = 3;
static const float DIVISION_HEIGTH = 6;
static const float SHIFT_DIVISION = -DIVISION_HEIGTH / 2.f;


class CShedule final
	: public CDrawable
	, private boost::noncopyable
{
public:
	CShedule(unsigned int width, unsigned int height);
	~CShedule();
//////////////////////////////////////////////////////////////////////
// Methods
public:

	void		Draw() const override;
	//--------------------------------------------
	// CDrawable
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------

	void		SetSize(unsigned int width, unsigned int height);
	void		AddParcticle(std::unique_ptr<CParticle> graph);

	//--------------------------------------------
	// ParticleSystem
	void		Advance(float dt);
	void		CreateSystem();
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<std::unique_ptr<CParticle>>	m_particles;
//////////////////////////////////////////////////////////////////////
// Methods
private:
//////////////////////////////////////////////////////////////////////
// Constants
private:
//////////////////////////////////////////////////////////////////////
// Data
private:
	CParticleSystem							m_system;
	std::vector<std::shared_ptr<CShape>>	m_gui;

	float									m_windowWidth = 0;
	float									m_windowHeigth = 0;
//////////////////////////////////////////////////////////////////////
};
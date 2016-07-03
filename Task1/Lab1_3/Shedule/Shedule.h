#pragma once

#pragma once

// Test 



#include "../Shape/Ball.h"
#include "PhysicalSystem.h"

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
	void		AddParcticle(std::unique_ptr<CDynamicBody> graph);

	//--------------------------------------------
	// PhysicSystem
	void										Advance(float dt);
	void										CreateSystem();

	CPhysicalSystem&							GetPhysicSystem();
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
public:
//////////////////////////////////////////////////////////////////////
// Methods
private:
//////////////////////////////////////////////////////////////////////
// Constants
private:
//////////////////////////////////////////////////////////////////////
// Data
private:
	CPhysicalSystem							m_system;
	std::vector<std::shared_ptr<CShape>>	m_gui;// TODO : add button if need

	float									m_windowWidth = 0;
	float									m_windowHeigth = 0;
//////////////////////////////////////////////////////////////////////
};
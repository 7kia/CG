#pragma once

#pragma once

#include "../Shape/Particle.h"
#include "LimitFunction.h"
#include "ArchimedeanSpiral.h"

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
// Methods
public:

	void		Draw() const override;
	// CDrawable
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		SetSize(unsigned int width, unsigned int height);
	void		AddParcticle(std::unique_ptr<CParticle> graph);
// Data
public:
	std::vector<std::unique_ptr<CParticle>>	m_particles;
// Methods
private:

// Constants
private:
	static const int						AMOUNT_DIVISIONS = 10;

	const float								ARROW_ANGLE = 35;// TODO : ask why not be static const float

	std::vector<std::pair<glm::vec2, float>>	PARAMETERS_DIVISIONS_AXIS =
												{
													{ glm::vec2(SCALE_FACTOR, 0.f), 0.f}
													, { glm::vec2(-SCALE_FACTOR, 0.f) , 0.f}

													, { glm::vec2(0.f, SCALE_FACTOR), 90.f}
													, { glm::vec2(0.f, -SCALE_FACTOR), 90.f}
												};

// Data
private:
	std::vector<std::shared_ptr<CShape>>	m_gui;

	float									m_windowWidth = 0;
	float									m_windowHeigth = 0;
};
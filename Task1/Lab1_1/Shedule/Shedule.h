#pragma once

#pragma once

#include "../Shape/Rectangle.h"
#include "LimitFunction.h"
#include "ArchimedeanSpiral.h"

#include <memory>
#include <vector>

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
	void		AddFunctionsGraphs(std::shared_ptr<CShape> graph);
// Data
public:
	std::vector<std::shared_ptr<CShape>>	m_functionsGraphs;
// Methods
private:
	void									CreateAxis();
	void									UpdateAxisProperties();

	void									CreateArrows();
	std::unique_ptr<CRectangle>				CreatePartArrow();
	std::unique_ptr<CRectangle>				CreateDivision();

	void									CreateDivisions();
	void									UpdateDivisionsProperties();
	void									AddListDivisions(const glm::vec2 & shift, float rotate);
// Constants
private:
	static const int						AMOUNT_DIVISIONS = 20;

	static const int						THIKNESS_LINES = 3;
	static const int						ARROW_WIDTH = 3;
	static const int						ARROW_HEIGTH = 25;

	static const int						DIVISION_WIDTH = 4;
	static const int						DIVISION_HEIGTH = 11;
	const float								SHIFT_DIVISION = -DIVISION_HEIGTH / 2.f;

	const float								ARROW_ANGLE = 35;// TODO : ask why not be static const float

	std::vector<std::pair<glm::vec2, float>>	PARAMETERS_DIVISIONS_AXIS =
												{
													{ glm::vec2(SCALE_FACTOR, 0.f), 0.f}
													, { glm::vec2(-SCALE_FACTOR, 0.f) , 0.f}

													, { glm::vec2(0.f, SCALE_FACTOR), 1.57f}
													, { glm::vec2(0.f, -SCALE_FACTOR), 1.57f}
												};

// Data
private:
	std::vector<std::shared_ptr<CShape>>	m_coordinateSystem;

	float									m_windowWidth = 0;
	float									m_windowHeigth = 0;
};
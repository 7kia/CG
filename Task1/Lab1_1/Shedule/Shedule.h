#pragma once

#pragma once

#include "../Shape/Rectangle.h"
#include "../Shape/FunctionGraph.h"

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

	void		AddFunctionsGraphs(std::shared_ptr<CShape> graph);
// Data
public:
	std::vector<std::shared_ptr<CShape>>	m_functionsGraphs;
// Methods
private:
	void									CreateAxis();
	void									CreateArrows();
	std::unique_ptr<CRectangle>				GetPartArrow();
	std::unique_ptr<CRectangle>				GetDivision();
	void									CreateDivisions();
	void									AddListDivisions(const glm::vec2 & shift, float rotate);
// Constants
private:
	static const int						AMOUNT_DIVISIONS = 10;

	static const int						THIKNESS_LINES = 3;
	static const int						ARROW_WIDTH = 3;
	static const int						ARROW_HEIGTH = 25;

	static const int						DIVISION_WIDTH = 3;
	static const int						DIVISION_HEIGTH = 6;
	const float								SHIFT_DIVISION = -DIVISION_HEIGTH / 2.f;


	const float								ARROW_ANGLE = 35;// TODO : ask why not be static const float
// Data
private:
	std::vector<std::shared_ptr<CShape>>	m_coordinateSystem;

	float									m_windowWidth = 0;
	float									m_windowHeigth = 0;
};
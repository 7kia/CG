#pragma once

#pragma once

#include "../Shape/Rectangle.h"

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
	void									CreateDivisions();
// Constants
private:
	static const int						THIKNESS_LINES = 3;
// Data
private:
	std::vector<std::shared_ptr<CShape>>	m_coordinateSystem;

	unsigned int							m_windowWidth = 0;
	unsigned int							m_windowHeigth = 0;
};
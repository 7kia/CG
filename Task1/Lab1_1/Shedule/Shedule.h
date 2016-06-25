#pragma once

#pragma once

#include "../Shape/CShape.h"

#include <memory>
#include <vector>

class CShedule final// was exported from third lab by OOP
	: public CDrawable
	, private boost::noncopyable

{
public:
	CShedule();
	~CShedule();

public:// Methods

	// CDrawable
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//

	void		AddFunctionsGraphs(std::shared_ptr<CShape> graph);
public:// Data
	std::vector<std::shared_ptr<CShape>>	m_functionsGraphs;

private:// Methods

private:// Data
};
#pragma once

#include <glm/vec3.hpp>
#include <boost/noncopyable.hpp>

class IShape : private boost::noncopyable
{
public:
	virtual void	SetOutlineColor(const glm::vec3 &centerColor) = 0;

	virtual void	Draw() const = 0;
	virtual void	Redraw() const = 0;

	virtual bool	HitTest(const glm::vec2 &point) const = 0;// TODO : might will be neccessary

private:
	virtual void	DeleteList() = 0;
};

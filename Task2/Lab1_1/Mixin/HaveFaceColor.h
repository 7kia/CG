#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Colors
{
	const glm::vec3 LIGHT_YELLOW = { 1.f, 1.f, 0.5f };
	const glm::vec3 RED = { 1, 0, 0 };
	const glm::vec3 ORANGE = { 1.f, 0.5f, 0.f };
	const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
	const glm::vec3 BLACK = { 0.f, 0.f, 0.f };
}

namespace TransparentColors
{
	const glm::vec4 QUIET_GREEN = { 0.f, 0.5f, 0.2f, 1.f };
}

class IHaveFaceColor
{
public:
	virtual ~IHaveFaceColor() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			SetFaceColor(const glm::vec3 &color) = 0;
	virtual glm::vec3		GetFaceColor() const = 0;
};

class CHaveFaceColor : public IHaveFaceColor
{
public:
	CHaveFaceColor();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetFaceColor(const glm::vec3 &color) override;
	glm::vec3				GetFaceColor() const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec3				m_faceColor;

};
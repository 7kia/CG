#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Colors
{
	const float DEFAULT_ALPHA = 1.f;
	const glm::vec4 LIGHT_YELLOW = { 1.f, 1.f, 0.5f, DEFAULT_ALPHA };
	const glm::vec4 RED = { 1, 0, 0, DEFAULT_ALPHA };
	const glm::vec4 ORANGE = { 1.f, 0.5f, 0.f, DEFAULT_ALPHA };
	const glm::vec4 YELLOW = { 1.f, 1.f, 0.f, DEFAULT_ALPHA };
	const glm::vec4 BLACK = { 0.f, 0.f, 0.f, DEFAULT_ALPHA };
}

class IHaveFaceColor
{
public:
	virtual ~IHaveFaceColor() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			SetFaceColor(const glm::vec4 &color) = 0;
	virtual glm::vec4		GetFaceColor() const = 0;

	virtual void			SetAlpha(float alpha) = 0;
	virtual float			GetAlpha() const = 0;

};

class CHaveFaceColor : public IHaveFaceColor
{
public:
	CHaveFaceColor();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetFaceColor(const glm::vec4 &color) override;
	glm::vec4				GetFaceColor() const override;

	void					SetAlpha(float alpha) override;
	float					GetAlpha() const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4				m_faceColor;

};
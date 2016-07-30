#pragma once

#include "IShape.h"

class CTetrahedron final : public IShape
{
public:
	void Update(float deltaTime) final;
	void Draw()const final;

	void SetColor(const glm::vec4 &color);

private:
	void OutputFaces()const;

	glm::vec4 m_color;
};
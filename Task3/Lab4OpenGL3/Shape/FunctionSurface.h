#pragma once

#include "Shape\3DShape.h"
#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

using Function3D = std::function<glm::vec3(float, float)>;
using uint = unsigned int;
// Вершина с трёхмерной позицией и нормалью.



class CSolidFunctionSurface final 
	: public CIdentity3DShape
{
public:
    CSolidFunctionSurface(const Function3D &xFunction);
//////////////////////////////////////////////////////////////////////
// Methods
public:
    /// Инициализирует индексированную сетку треугольников
    /// @param rangeX - диапазон, где x - нижняя граница, y - верхняя граница
    /// @param rangeZ - диапазон, где x - нижняя граница, y - верхняя граница
	void	Tesselate(const glm::vec2 &rangeU
					, const glm::vec2 &rangeV
					, float step);

	void	Update(float twist);// TODO : rename twist
	//--------------------------------------------
    // CShape 
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	Function3D		m_function;// TODO : see will rewrite this part

	glm::vec2		m_rangeU;
	glm::vec2		m_rangeV;
	float			m_step;

};

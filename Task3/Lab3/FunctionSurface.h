#pragma once

#include "Shape\3DShape.h"
#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

using Function2D = std::function<float(float, float)>;
using uint = unsigned int;
// Вершина с трёхмерной позицией и нормалью.



class CSolidFunctionSurface final 
	: public CIdentity3DShape
{
public:
    CSolidFunctionSurface(const Function2D &xFunction
						, const Function2D &yFunction
						, const Function2D &zFunction);
//////////////////////////////////////////////////////////////////////
// Methods
public:
    /// Инициализирует индексированную сетку треугольников
    /// @param rangeX - диапазон, где x - нижняя граница, y - верхняя граница
    /// @param rangeZ - диапазон, где x - нижняя граница, y - верхняя граница
    void Tesselate(const glm::vec2 &rangeU
					, const glm::vec2 &rangeV
					, float step);
	//--------------------------------------------
    // CShape 
    void Draw() const override final;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	Function2D					m_xFunction;// TODO : see will rewrite this part
	Function2D					m_yFunction;
	Function2D					m_zFunction;

    std::vector<SVertexP3NT2>		m_vertices;
    std::vector<uint32_t>		m_indicies;
};

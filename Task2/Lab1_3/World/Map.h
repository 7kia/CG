#pragma once

#include "../Mixin/HaveFileForReading.h"
#include "Wall.h"
#include "../Decorators/TransformShapeDecorator.h"
#include <string>
#include <vector>

namespace MapSpace
{
	static const char RecognizeSymbols[] = {
		  '+'
		, ' '
		, '0'
	};
}

class CMap
	: public CHaveFileForReading
	, public IDrawable
	, public IUpdatable
{
public:
	CMap(const std::string & mapPath);
	virtual ~CMap() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void	Draw() const override final;
	void	Update(float deltaTime) override final;
private:
	void	ReadMap(std::ifstream & file);
	void	ProcessRow(const std::string & row, unsigned widthCount, int level);

	void	AddTopLevel(unsigned length, unsigned width);
	void	AddMiddleLevel(unsigned length, unsigned width);
	void	AddLowLevel(unsigned length, unsigned width);

	void	AddWall(unsigned x, unsigned y, int z);
	void	ProcessLateralEdge(CWall* pWall
								, const glm::vec3 & position
								, const glm::vec3 & shifts);
	void	ProcessVerticalEdge(CWall* pWall
								, const glm::vec3 & position
								, int zShift);


	void	ComputeVisibleEdge(unsigned length, unsigned width);
//////////////////////////////////////////////////////////////////////
// Data
private:

	enum class IdSymbol
	{
		  Wall = 0
		, Space
		, Player
	};
	using Level = std::vector<std::string>;

	glm::vec2						m_centerMap;
	std::vector<IBodyUniquePtr>		m_walls;
	std::vector<Level>				m_map;
};
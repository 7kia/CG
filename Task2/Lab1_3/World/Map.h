#pragma once

#include "../Mixin/HaveFileForReading.h"
#include "Wall/Wall.h"
#include <string>
#include <vector>

namespace MapSpace
{
	static const char RecognizeSymbols[] = {
		  '+'
		, ' '
		, '0'
	};

	static const int SIZE_BORDER = 1;
}

class CWorld;

class CMap
	: public CHaveFileForReading
	, public IDrawable
	, public IUpdatable
{
public:
	CMap(const std::string & mapPath, CWorld* pWorld);

	virtual ~CMap() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IDrawable
	void					Draw() const override final;
	//--------------------------------------------
	// IUpdatable
	void					Update(float deltaTime) override final;
	//--------------------------------------------
private:
	void					ReadMap(std::ifstream & file);
	void					ProcessRow(const std::string & row, size_t widthCount, int level);

	void					AddTopLevel(size_t length, size_t width);
	void					AddMiddleLevel(size_t length, size_t width);
	void					AddLowLevel(size_t length, size_t width);

	void					AddWall(const glm::vec3 & position
									, size_t length
									, size_t width); 
	void					ProcessLateralEdge(CWall* pWall
												, const glm::vec3 & position
												, const glm::vec3 & shifts);
	void					ProcessVerticalEdge(CWall* pWall
												, const glm::vec3 & position
												, int zShift);

	static unsigned			GetIndexWallType(const glm::vec3 & position
											, size_t length
											, size_t width);
	static unsigned			WallHaveCollision(int heigth);
	static std::string		GenerateRowOfWalls(unsigned length, const std::string & borderRow);
	static void				AddBorderSymbolsForRow(std::string & row);

	void					ComputeVisibleEdge(size_t width);
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
	std::vector<IActorUniquePtr>	m_walls;
	std::vector<Level>				m_map;

	CWorld*							pWorld = nullptr;
	bool							m_addPlayer = false;
};
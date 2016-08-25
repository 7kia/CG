#pragma once

#include "../Mixin/HaveFileForReading.h"
#include "Wall/Wall.h"
#include "Labyrinth.h"
#include <string>
#include <vector>

namespace MapSpace
{
	static const uint8_t RecognizeSymbols[] = {
		// 
		//  '+'
		//, ' '
		//, '0'
		  0x0// Wall
		, 0x1// Player
		, 0x2// Spaxe
	};

	static const int SIZE_BORDER = 1;
}

class CWorld;

class CMap
	: public IActor
{
public:
	CMap() = default;
	CMap(const std::string & mapPath, CWorld* pWorld);

	virtual ~CMap() = default;

	using Row = std::vector<uint8_t>;
	using Level = std::vector<std::vector<uint8_t>>;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IDrawable
	void							Draw() const override final;
	//--------------------------------------------
	// IUpdatable
	void							Update(float deltaTime) override final;
	//--------------------------------------------

	void							Create(const std::string & mapPath, CWorld* pWorld);
private:
	enum class IdSymbol
	{
		Wall = 0
		, Player
		, Space
	};
	enum class NameLevels
	{
		Floor = -1
		, Wall = 0
		, Ñeiling = 1
	};

	void					ReadMap(const std::string & mapPath);
	void					ProcessRow(const Row & row, size_t widthCount, int level);

	void					AddTopLevel(size_t length, size_t width);
	void					AddMiddleLevel(SDL_Surface & surface);
	void					AddLowLevel(size_t length, size_t width);

	void					AddWall(const glm::vec3 & position
									, size_t length
									, size_t width); 
	void					AddPlayer(const glm::vec3 & position);
	void					DefineVisibleLateralEdge(CWall* pWall
												, const glm::vec3 & position
												, const glm::vec3 & shifts);
	void					DefineVisibleVerticalEdge(CWall* pWall
												, const glm::vec3 & position
												, int zShift);
	void					DefineVisibleLateralEdgeForPlayer(CWall* pWall
																, const glm::vec3 & position
																, const glm::vec3 & shifts);
	void					DefineVisibleVerticalEdgeForPlayer(CWall* pWall
																, const glm::vec3 & position
																, int zShift);

	static size_t			GetIndexWallType(const glm::vec3 & position
											, size_t length
											, size_t width);
	static bool				WallHaveCollision(int heigth);
	static Row				GenerateRowOfWalls(const Row & borderRow);
	static void				AddBorderSymbolsForRow(Row & row);


	void					ComputeVisibleEdge(size_t width);
	void					SetWorld(CWorld* pWorld);
//////////////////////////////////////////////////////////////////////
// Data
private:

	glm::vec2						m_centerMap;
	std::vector<Level>				m_map;

	CLabyrinth						m_labyrinth;

	CWorld*							m_pWorld = nullptr;
	bool							m_addPlayer = false;
};
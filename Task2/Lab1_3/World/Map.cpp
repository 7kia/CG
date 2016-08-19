#include "stdafx.h"
#include "Map.h"
#include "World.h"

using namespace std;
using namespace MapSpace;

CMap::CMap(const string & mapPath, CWorld* pWorld)
	: CHaveFileForReading()
	, IActor()
	, pWorld(pWorld)
{
	CheckAndOpenFileForReading(mapPath);
	ReadMap(m_inputFile);
}

void CMap::Draw() const
{
	// TODO : not work
	m_labyrinth.Draw();
}

void CMap::Update(float deltaTime)
{
	(void)deltaTime;
}

void CMap::ReadMap(ifstream & file)
{
	size_t length = 0;
	size_t width = 0;

	file >> length;
	file >> width;

	m_centerMap = glm::vec2((length / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE
							, (width / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE);

	// Order changed for optimization
	AddMiddleLevel(length, width);
	AddTopLevel(length, width);
	AddLowLevel(length, width);

	ComputeVisibleEdge(width);

	//m_labyrinth.BuildLabyrinth(GetWalls());
}

void CMap::ProcessRow(const std::string & row, size_t widthCount, int level)
{
	for (size_t index = 0; index < row.size(); ++index)
	{
		if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Player)])
		{
			AddPlayer(glm::vec3(index, widthCount, level));
		}
		else if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Space)])
		{

		}
		else if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
		{
			AddWall(glm::vec3(index, widthCount, level), row.size(), m_map[0].size());
		}		
	}
}

void CMap::AddTopLevel(size_t length, size_t width)
{
	Level topLevel;

	for (size_t y = 0; y < (width + 2 * MapSpace::SIZE_BORDER); ++y)
	{
		string row;
		for (size_t x = 0; x < (length + 2 * MapSpace::SIZE_BORDER); ++x)
		{
			if ((m_map[0][y][x] != RecognizeSymbols[unsigned(IdSymbol::Wall)])
				&& IsBetween(x, size_t(1), m_map[0][0].size() - 2)
				&& IsBetween(y, size_t(1), m_map[0].size() - 2) )
			{
				row += RecognizeSymbols[unsigned(IdSymbol::Wall)];
			}
			else
			{
				row += RecognizeSymbols[unsigned(IdSymbol::Space)];
			}
		}
		topLevel.push_back(row);
	}

	m_map.emplace_back(topLevel);
}

void CMap::AddMiddleLevel(size_t length, size_t width)
{
	size_t widthCount = 0;

	Level middleLevel;
	string inputString;
	getline(m_inputFile, inputString);// pass string
	while (getline(m_inputFile, inputString))
	{
		if (widthCount > (width - 1))
		{
			throw std::runtime_error("Width labyrinth not correspond expected");
		}
		if (inputString.size() != length)
		{
			throw std::runtime_error("Length row not correspond expected");
		}
		// Add in start and end border symbols
		AddBorderSymbolsForRow(inputString);
		middleLevel.push_back(inputString);
	}
	// Top border row
	middleLevel.insert(middleLevel.begin(), GenerateRowOfWalls(middleLevel.front()));
	// Low border row
	middleLevel.push_back(GenerateRowOfWalls(middleLevel.back()));

	m_map.push_back(middleLevel);
}

std::string CMap::GenerateRowOfWalls(const std::string & borderRow)
{
	std::string result;
	for (size_t index = 1; index < (borderRow.size() - 1); ++index)
	{
		if (borderRow[index] == RecognizeSymbols[unsigned(IdSymbol::Space)])
		{
			result += RecognizeSymbols[unsigned(IdSymbol::Wall)];
		}
		else
		{
			result += RecognizeSymbols[unsigned(IdSymbol::Space)];
		}
	}
	// Border symbols
	result.insert(result.begin(), RecognizeSymbols[unsigned(IdSymbol::Space)]);
	result.insert(result.end(), RecognizeSymbols[unsigned(IdSymbol::Space)]);

	return result;
}

void CMap::AddBorderSymbolsForRow(std::string & row)
{
	InsertSymbolInRow(row
					, row.end()
					, row.end() - 1
					, IdSymbol::Space
					, IdSymbol::Wall);
	InsertSymbolInRow(row
					, row.begin()
					, row.begin()
					, IdSymbol::Space
					, IdSymbol::Wall);
}

void CMap::InsertSymbolInRow(std::string & row
							, std::string::const_iterator where
							, std::string::const_iterator checkSymbol
							, CMap::IdSymbol insteadWall
							, CMap::IdSymbol insteadSpace)
{
	if (*checkSymbol != RecognizeSymbols[unsigned(insteadSpace)])
	{
		row.insert(where, RecognizeSymbols[unsigned(insteadSpace)]);
	}
	else
	{
		row.insert(where, RecognizeSymbols[unsigned(insteadWall)]);
	}
}

void CMap::AddLowLevel(size_t length, size_t width)
{
	Level lowLevel;

	for (size_t y = 0; y < (width + 2 * MapSpace::SIZE_BORDER); ++y)
	{
		string row;
		for (size_t x = 0; x < (length + 2 * MapSpace::SIZE_BORDER); ++x)
		{
			if ((m_map[1][y][x] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
				&& IsBetween(x, size_t(1), m_map[0][0].size() - 1 - MapSpace::SIZE_BORDER)
				&& IsBetween(y, size_t(1), m_map[0].size() - 1 - MapSpace::SIZE_BORDER))
			{
				row += RecognizeSymbols[unsigned(IdSymbol::Wall)];
			}
			else
			{
				row += RecognizeSymbols[unsigned(IdSymbol::Space)];
			}

		}
		lowLevel.push_back(row);
	}

	m_map.emplace(m_map.begin(), lowLevel);
}

void CMap::ProcessLateralEdge(CWall* pWall
							, const glm::vec3 & position
							, const glm::vec3 & shifts)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	size_t z = size_t(position.z);
	int xShift = int(shifts.x);
	int yShift = int(shifts.y);
	int zShift = int(shifts.z);

	if (((int(x) + xShift) >= 0) && ((int(y) + yShift) >= 0)
		&& ((int(x) + xShift) < m_map[0].size()) && ((int(y) + yShift) < m_map[0].size()))
	{
		if (m_map[z + 1][y + yShift][x + xShift] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
		{
			if ((xShift == 0) && (yShift == 1) && ((int(z + 1) + zShift) == 0))
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Front), false);
			}
			else if ((xShift == 1) && (yShift == 0) && ((int(z + 1) + zShift) == 0))
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Right), false);
			}
			else if ((xShift == 0) && (yShift == -1) && ((int(z + 1) + zShift) == 0))
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Back), false);
			}
			else if ((xShift == -1) && (yShift == 0) && ((int(z + 1) + zShift) == 0))
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Left), false);
			}

		}
	}

}

void CMap::ProcessVerticalEdge(CWall * pWall, const glm::vec3 & position, int zShift)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	size_t z = size_t(position.z);

	if (IsBetween(x, size_t(0), m_map[0].size())
		&& IsBetween(y, size_t(0), m_map[0].size())
		&& IsBetween(int(z + 1) + zShift, 0, int(m_map.size() - 1))
		)
	{
		if (m_map[z + 1 + zShift][y][x] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
		{
			if (zShift == 1)
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Top), false);
			}
			else if (zShift == -1)
			{
				pWall->SetVisible(unsigned(WallSpace::CubeFace::Bottom), false);
			}
		}
	}

}

void CMap::ComputeVisibleEdge(size_t width)
{
	for (size_t height = 0; height < 3; ++height)
	{
		string* row = nullptr;
		for (size_t y = 0; y < (width + 2 * MapSpace::SIZE_BORDER); ++y)
		{
			row = &m_map[height][y];

			ProcessRow(*row, y, int(height - 1));
		}
	}
}



unsigned CMap::GetIndexWallType(const glm::vec3 & position
	, size_t length
	, size_t width)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int heigth = int(position.z);
	switch (heigth)
	{
	case -1: case 1:
		return unsigned(CHaveWallTypes::IdWallType::Plank);
	case 0:
		if ((x == 0) || (x == length - 1)
			|| (y == 0) || (y == width - 1))
		{
			return unsigned(CHaveWallTypes::IdWallType::Arch);
		}
		return unsigned(CHaveWallTypes::IdWallType::Break);
	default:
		throw std::runtime_error("Incorrect index");
		break;
	}
}

bool CMap::WallHaveCollision(int heigth)
{
	switch (heigth)
	{
		// TODO: create enum with list of height values as constants
	case -1: case 1: // TODO: what is -1? what is 1?
		return false;
	case 0: // TODO: what is 0?
		return true;
	default:
		throw std::runtime_error("Incorrect index");
	}
}

void CMap::AddWall(const glm::vec3 & position
	, size_t length
	, size_t width)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int z = int(position.z);

	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_shared<CWall>();
	pWall->SetType(pWorld->GetWallType(GetIndexWallType(position, length, width)));

	for (int xShift = -1; xShift <= 1; ++xShift)
	{
		for (int yShift = -1; yShift <= 1; ++yShift)// this loop and high for process around wall
		{
			for (int zShift = -1; zShift <= 1; ++zShift)
			{

				if (abs(xShift) != abs(yShift))// not process itself
				{
					ProcessLateralEdge(pWall.get(), position, glm::vec3(xShift, yShift, zShift));
				}
				else if ((xShift == 0) && (yShift == 0))
				{
					ProcessVerticalEdge(pWall.get(), position, zShift);
				}

			}
		}
	}

	// SetPosition duplicate because before call AddToWorld must set position
	pWall->SetPosition(glm::vec3(xPosition, z * WallSpace::SIZE, yPosition));
	pWall->SetHaveCollision(WallHaveCollision(z));

	if (pWall->GetHaveCollision())
	{
		pWall->SetPosition(glm::vec3(xPosition, z * WallSpace::SIZE, yPosition));
		pWall->AddToWorld(pWorld->GetWorld());
	}

	m_labyrinth.AddWall(pWall);

	//m_walls.emplace_back(std::move(pWall));
}

void CMap::AddPlayer(const glm::vec3 & position)
{
	float xPosition = WallSpace::SIZE * position.x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * position.y - m_centerMap.y;

	pWorld->SetSpawnPoint(glm::vec3(xPosition, yPosition, position.z * WallSpace::SIZE));
}

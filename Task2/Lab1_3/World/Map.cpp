#include "stdafx.h"
#include "Map.h"
#include "World.h"

using namespace std;
using namespace MapSpace;

CMap::CMap(const string & mapPath, CWorld* pWorld)
	: CHaveFileForReading()
	, IActor()
{
	Create(mapPath, pWorld);
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

void CMap::Create(const std::string & mapPath, CWorld * pWorld)
{
	SetWorld(pWorld);
	CheckAndOpenFileForReading(mapPath);
	ReadMap(m_inputFile);

	m_labyrinth.ReallocateMemory();
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
		if (row[index] == RecognizeSymbols[size_t(IdSymbol::Player)])
		{
			AddPlayer(glm::vec3(index, widthCount, level));
		}
		else if (row[index] == RecognizeSymbols[size_t(IdSymbol::Space)])
		{

		}
		else if (row[index] == RecognizeSymbols[size_t(IdSymbol::Wall)])
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
			
			/*
			if ((m_map[0][y][x] != RecognizeSymbols[size_t(IdSymbol::Wall)])
				&& IsBetween(x, size_t(1), m_map[0][0].size() - 2)
				&& IsBetween(y, size_t(1), m_map[0].size() - 2) )
			{
				row += RecognizeSymbols[size_t(IdSymbol::Wall)];
			}
			else
			{
				row += RecognizeSymbols[size_t(IdSymbol::Space)];
			}
			*/
			row += RecognizeSymbols[size_t(IdSymbol::Wall)];
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
		/*
		if (borderRow[index] == RecognizeSymbols[size_t(IdSymbol::Space)])
		{
			result += RecognizeSymbols[size_t(IdSymbol::Wall)];
		}
		else
		{
			result += RecognizeSymbols[size_t(IdSymbol::Space)];
		}
		*/
		result += RecognizeSymbols[size_t(IdSymbol::Wall)];
		
	}
	// Border symbols
	result.insert(result.begin(), RecognizeSymbols[size_t(IdSymbol::Wall)]);
	result.insert(result.end(), RecognizeSymbols[size_t(IdSymbol::Wall)]);

	return result;
}

void CMap::AddBorderSymbolsForRow(std::string & row)
{
	row.insert(row.begin(), RecognizeSymbols[size_t(IdSymbol::Wall)]);
	row.push_back(RecognizeSymbols[size_t(IdSymbol::Wall)]);
}

void CMap::InsertSymbolInRow(std::string & row
							, std::string::const_iterator where
							, std::string::const_iterator checkSymbol
							, CMap::IdSymbol insteadWall
							, CMap::IdSymbol insteadSpace)
{
	if (*checkSymbol != RecognizeSymbols[size_t(insteadSpace)])
	{
		row.insert(where, RecognizeSymbols[size_t(insteadSpace)]);
	}
	else
	{
		row.insert(where, RecognizeSymbols[size_t(insteadWall)]);
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
			row += RecognizeSymbols[size_t(IdSymbol::Wall)];
		}
		lowLevel.push_back(row);
	}

	m_map.emplace(m_map.begin(), lowLevel);
}

void CMap::DefineVisibleLateralEdge(CWall* pWall
							, const glm::vec3 & position
							, const glm::vec3 & shifts)
{
	int x = int(position.x);
	int y = int(position.y);
	int z = int(position.z);
	int xShift = int(shifts.x);
	int yShift = int(shifts.y);
	int zShift = int(shifts.z);

	if (((x + xShift) >= 0) && ((y + yShift) >= 0)
		&& ((x + xShift) < m_map[0].size()) && ((y + yShift) < m_map[0].size()))
	{
		if (m_map[z + 1][y + yShift][x + xShift] == RecognizeSymbols[size_t(IdSymbol::Wall)])
		{
			if ((xShift == 0) && (yShift == 1) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Front), false);
			}
			else if ((xShift == 1) && (yShift == 0) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Right), false);
			}
			else if ((xShift == 0) && (yShift == -1) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Back), false);
			}
			else if ((xShift == -1) && (yShift == 0) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Left), false);
			}

		}
	}

}

void CMap::DefineVisibleVerticalEdge(CWall * pWall, const glm::vec3 & position, int zShift)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int z = int(position.z);

	if (IsBetween(x, size_t(0), m_map[0].size())
		&& IsBetween(y, size_t(0), m_map[0].size())
		&& IsBetween(z + 1 + zShift, 0, int(m_map.size() - 1))
		)
	{
		if (m_map[z + 1 + zShift][y][x] == RecognizeSymbols[size_t(IdSymbol::Wall)])
		{
			if (zShift == 1)
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Top), true);
			}
			else if (zShift == -1)
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Bottom), true);
			}
		}
	}

}

void CMap::DefineVisibleLateralEdgeForPlayer(CWall* pWall
											, const glm::vec3 & position
											, const glm::vec3 & shifts)
{
	int x = int(position.x);
	int y = int(position.y);
	int z = int(position.z);
	int xShift = int(shifts.x);
	int yShift = int(shifts.y);
	int zShift = int(shifts.z);

	if (((x + xShift) >= 0) && ((y + yShift) >= 0)
		&& ((x + xShift) < m_map[0].size()) && ((y + yShift) < m_map[0].size()))
	{
		if (m_map[z + 1][y + yShift][x + xShift] != RecognizeSymbols[size_t(IdSymbol::Wall)])
		{
			if ((xShift == 0) && (yShift == 1) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Front), true);
			}
			else if ((xShift == 1) && (yShift == 0) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Right), true);
			}
			else if ((xShift == 0) && (yShift == -1) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Back), true);
			}
			else if ((xShift == -1) && (yShift == 0) && ((z + 1 + zShift) == 0))
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Left), true);
			}

		}
	}
}

void CMap::DefineVisibleVerticalEdgeForPlayer(CWall* pWall
												, const glm::vec3 & position
												, int zShift)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int z = int(position.z);

	if (IsBetween(x, size_t(0), m_map[0].size())
		&& IsBetween(y, size_t(0), m_map[0].size())
		&& IsBetween(z + 1 + zShift, 0, int(m_map.size() - 1))
		)
	{
		if (m_map[z + 1 + zShift][y][x] != RecognizeSymbols[size_t(IdSymbol::Wall)])
		{
			if (zShift == 1)
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Top), true);
			}
			else if (zShift == -1)
			{
				pWall->SetVisible(size_t(WallSpace::CubeFace::Bottom), true);
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

void CMap::SetWorld(CWorld * pWorld)
{
	m_pWorld = pWorld;
}



size_t CMap::GetIndexWallType(const glm::vec3 & position
							, size_t length
							, size_t width)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int heigth = int(position.z);
	switch (heigth)
	{
	case -1: case 1:
		return size_t(WallTypeSpace::Id::Plank);
	case 0:
		if ((x == 0) || (x == length - 1)
			|| (y == 0) || (y == width - 1))
		{
			return size_t(WallTypeSpace::Id::Arch);
		}
		return size_t(WallTypeSpace::Id::Break);
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
	pWall->SetType(m_pWorld->GetWallType(GetIndexWallType(position, length, width)));
	pWall->SetVisible(false);

	// Next define visible edge for player
	for (int xShift = -1; xShift <= 1; ++xShift)
	{
		for (int yShift = -1; yShift <= 1; ++yShift)// this loop and high for process around wall
		{
			for (int zShift = -1; zShift <= 1; ++zShift)
			{
				if (abs(xShift) != abs(yShift))// not process itself
				{
					DefineVisibleLateralEdgeForPlayer(pWall.get(), position, glm::vec3(xShift, yShift, zShift));
				}
				else if ((xShift == 0) && (yShift == 0))
				{
					DefineVisibleVerticalEdgeForPlayer(pWall.get(), position, zShift);
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
		pWall->AddToWorld(m_pWorld->GetWorld());
	}

	m_labyrinth.AddWall(pWall, z + 1);
}

void CMap::AddPlayer(const glm::vec3 & position)
{
	float xPosition = WallSpace::SIZE * position.x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * position.y - m_centerMap.y;

	m_pWorld->SetSpawnPoint(glm::vec3(xPosition, yPosition, position.z * WallSpace::SIZE));
}

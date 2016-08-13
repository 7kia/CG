#include "stdafx.h"
#include "Map.h"

using namespace std;
using namespace MapSpace;

CMap::CMap(const string & mapPath, CWorld* pWorld)
	: CHaveFileForReading()
	, IDrawable()
	, IUpdatable()
	, pWorld(pWorld)
{
	CheckAndOpenFileForReading(mapPath);
	ReadMap(m_inputFile);
}

void CMap::Draw() const
{
	for (const auto & wall : m_walls)
	{
		wall->Draw();
	}
}

void CMap::Update(float deltaTime)
{
	for (const auto & wall : m_walls)
	{
		wall->Update(deltaTime);
	}
}

void CMap::ReadMap(ifstream & file)
{
	size_t length = 0;
	size_t width = 0;

	file >> length;
	file >> width;

	m_centerMap = glm::vec2((length / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE
							, (width / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE);

	AddLowLevel(length, width);
	AddMiddleLevel(length, width);
	AddTopLevel(length, width);

	ComputeVisibleEdge(width);
}

void CMap::ProcessRow(const std::string & row, size_t widthCount, int level)
{
	for (size_t index = 0; index < row.size(); ++index)
	{
		if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Player)])
		{

		}
		else if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Space)])
		{

		}
		else if (row[index] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
		{
			AddWall(index, widthCount, level);
		}
		/*// TODO : see why swith not work
		switch (cell)
		{
		case RecognizeSymbols[unsigned(IdSymbol::Player)]:
			break;
		default:
			break;
		}
		*/
		
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
			row += RecognizeSymbols[unsigned(IdSymbol::Space)];
		}
		topLevel.push_back(row);
	}

	m_map.emplace_back(topLevel);
}

void CMap::AddMiddleLevel(size_t length, size_t width)
{
	unsigned widthCount = 0;

	Level middleLevel;
	string inputString;
	getline(m_inputFile, inputString);// pass string
	middleLevel.push_back(GenerateRowOfWalls(length));// Border row
	while (getline(m_inputFile, inputString))
	{
		if (widthCount > (width - 1))
		{
			throw std::runtime_error("Width labyrinth more expected");
		}
		if (inputString.size() > length)
		{
			throw std::runtime_error("Length row more expected");
		}
		// Add in start and end border symbols
		inputString.insert(inputString.begin(), RecognizeSymbols[unsigned(IdSymbol::Wall)]);
		inputString.insert(inputString.end(), RecognizeSymbols[unsigned(IdSymbol::Wall)]);
		middleLevel.push_back(inputString
								);
	}
	middleLevel.push_back(GenerateRowOfWalls(length));// Border row

	m_map.push_back(middleLevel);
}

std::string CMap::GenerateRowOfWalls(unsigned length)
{
	return std::string(length + 2 * MapSpace::SIZE_BORDER, RecognizeSymbols[unsigned(IdSymbol::Wall)]);
}

void CMap::AddLowLevel(size_t length, size_t width)
{
	Level lowLevel;

	for (unsigned y = 0; y < (width + 2 * MapSpace::SIZE_BORDER); ++y)
	{
		string row;
		for (unsigned x = 0; x < (length + 2 * MapSpace::SIZE_BORDER); ++x)
		{
			row += RecognizeSymbols[unsigned(IdSymbol::Wall)];
		}
		lowLevel.push_back(row);
	}

	m_map.emplace_back(lowLevel);
}

void CMap::ProcessLateralEdge(CWall* pWall
							, const glm::vec3 & position
							, const glm::vec3 & shifts)
{
	unsigned x = unsigned(position.x);
	unsigned y = unsigned(position.y);
	unsigned z = unsigned(position.z);
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
	unsigned x = unsigned(position.x);
	unsigned y = unsigned(position.y);
	unsigned z = unsigned(position.z);

	if ((x >= 0) && (y >= 0)
		&& IsBetween(int(z + 1) + zShift, 0, int(m_map.size()))
		&& (x < m_map[0].size()) && (y < m_map[0].size()))
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
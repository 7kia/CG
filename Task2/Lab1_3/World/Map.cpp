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

	// Order changed for optimization
	AddMiddleLevel(length, width);
	AddTopLevel(length, width);
	AddLowLevel(length, width);

	ComputeVisibleEdge(width);
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
	unsigned widthCount = 0;

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
	middleLevel.insert(middleLevel.begin(), GenerateRowOfWalls(length, middleLevel.front()));
	// Low border row
	middleLevel.push_back(GenerateRowOfWalls(length, middleLevel.back()));

	m_map.push_back(middleLevel);
}

std::string CMap::GenerateRowOfWalls(unsigned length, const std::string & borderRow)
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
	if (row.front() != RecognizeSymbols[unsigned(IdSymbol::Wall)])
	{
		row.insert(row.begin(), RecognizeSymbols[unsigned(IdSymbol::Wall)]);
	}
	else
	{
		row.insert(row.begin(), RecognizeSymbols[unsigned(IdSymbol::Space)]);
	}
	if (row.back() != RecognizeSymbols[unsigned(IdSymbol::Wall)])
	{
		row.insert(row.end(), RecognizeSymbols[unsigned(IdSymbol::Wall)]);
	}
	else
	{
		row.insert(row.end(), RecognizeSymbols[unsigned(IdSymbol::Space)]);
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
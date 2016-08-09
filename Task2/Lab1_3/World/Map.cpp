#include "stdafx.h"
#include "Map.h"

using namespace std;
using namespace MapSpace;

CMap::CMap(const string & mapPath)
	: CHaveFileForReading()
	, IDrawable()
	, IUpdatable()
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
	unsigned length = 0;
	unsigned width = 0;

	file >> length;
	file >> width;

	m_centerMap = glm::vec2((length / 2.f) * WallSpace::SIZE, (width / 2.f) * WallSpace::SIZE);

	AddLowLevel(length, width);
	AddMiddleLevel(length, width);
	AddTopLevel(length, width);

	ComputeVisibleEdge(length, width);
}

void CMap::ProcessRow(const std::string & row, unsigned widthCount, int level)
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

void CMap::AddTopLevel(unsigned length, unsigned width)
{
	Level topLevel;

	for (unsigned y = 0; y < width; ++y)
	{
		string row;
		for (unsigned x = 0; x < length; ++x)
		{
			row += RecognizeSymbols[unsigned(IdSymbol::Space)];
		}
		topLevel.push_back(row);
	}

	m_map.emplace_back(topLevel);
}

void CMap::AddMiddleLevel(unsigned length, unsigned width)
{
	unsigned widthCount = 0;

	Level middleLevel;
	string inputString;
	getline(m_inputFile, inputString);// pass string
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

		middleLevel.push_back(inputString);
	}
	m_map.push_back(middleLevel);
}

void CMap::AddLowLevel(unsigned length, unsigned width)
{
	Level lowLevel;

	for (unsigned y = 0; y < width; ++y)
	{
		string row;
		for (unsigned x = 0; x < length; ++x)
		{
			row += RecognizeSymbols[unsigned(IdSymbol::Wall)];
		}
		lowLevel.push_back(row);
	}

	m_map.emplace_back(lowLevel);
}

void CMap::AddWall(unsigned x, unsigned y, int z)
{
	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_unique<CWall>();


	for (int xShift = -1; xShift <= 1; ++xShift)
	{
		for (int yShift = -1; yShift <= 1; ++yShift)// this and high for process around wall
		{
			if (abs(xShift) != abs(yShift))// not process itself
			{
				// 
				if ( ((int(x) + xShift) >= 0) && ((int(y) + yShift) >= 0) 
					&& ((int(x) + xShift) < m_map[0].size()) && ((int(y) + yShift) < m_map[0].size()))
				{
					if (m_map[z + 1][y + yShift][x + xShift] == RecognizeSymbols[unsigned(IdSymbol::Wall)])
					{
						if ((xShift == 0) && (yShift == 1))
						{
							pWall->SetVisible(unsigned(WallSpace::CubeFace::Front), false);
						}
						else if ((xShift == 1) && (yShift == 0))
						{
							pWall->SetVisible(unsigned(WallSpace::CubeFace::Right), false);
						}
						else if ((xShift == 0) && (yShift == -1))
						{
							pWall->SetVisible(unsigned(WallSpace::CubeFace::Back), false);
						}
						else if ((xShift == -1) && (yShift == 0))
						{
							pWall->SetVisible(unsigned(WallSpace::CubeFace::Left), false);
						}
					}
				}
				

			}
		}
	}
	

	auto pTransform = std::make_unique<CTransformShapeDecorator>();
	pTransform->SetChild(std::move(pWall));
	pTransform->SetTransform(glm::translate(glm::mat4(), { xPosition, z * WallSpace::SIZE, yPosition }));

	m_walls.emplace_back(std::move(pTransform));
}

void CMap::ComputeVisibleEdge(unsigned length, unsigned width)
{
	for (unsigned height = 0; height < 3; ++height)
	{
		string* row = nullptr;
		for (unsigned y = 0; y < width; ++y)
		{
			row = &m_map[height][y];

			ProcessRow(*row, y, height - 1);
		}
	}
}

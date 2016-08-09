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
		ProcessRow(row, y, 1);
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

		ProcessRow(inputString, widthCount++, 0);
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
		ProcessRow(row, y, -1);
		lowLevel.push_back(row);
	}

	m_map.emplace_back(lowLevel);
}

void CMap::AddWall(unsigned x, unsigned y, int z)
{
	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_unique<CWall>();
	auto pTransform = std::make_unique<CTransformShapeDecorator>();
	pTransform->SetChild(std::move(pWall));
	pTransform->SetTransform(glm::translate(glm::mat4(), { xPosition, z * WallSpace::SIZE, yPosition }));

	m_walls.emplace_back(std::move(pTransform));
}

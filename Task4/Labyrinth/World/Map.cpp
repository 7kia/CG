#include "stdafx.h"
#include "Map.h"
#include "World.h"
#include "../Material/Texture2D.h"

using namespace std;
using namespace MapSpace;

std::once_flag mapIsCreate;

CMap::CMap(const string & mapPath, CWorld* pWorld)
	: IActor()
{
	Create(mapPath, pWorld);

	// Clear map, next it not need
	m_map.clear();
}

void CMap::Draw() const
{
	m_labyrinth.Draw();
}

void CMap::Update(float deltaTime)
{
	(void)deltaTime;
}

void CMap::Create(const std::string & mapPath, CWorld * pWorld)
{
	std::call_once(mapIsCreate, 
		[&]() {
			SetWorld(pWorld);

			ReadMap(mapPath);

			m_labyrinth.ShrinkToFit();
		}
	);
}

void CMap::ReadMap(const std::string & mapPath)
{
	SDLSurfacePtr pSurface(SDL_LoadBMP(mapPath.c_str()), SDL_FreeSurface);
	if (!pSurface)
	{
		throw std::runtime_error("Cannot find texture at " + mapPath);
	}

	const GLenum pixelFormat = GL_RGB;
	switch (pSurface->format->format)
	{
	case SDL_PIXELFORMAT_INDEX8:
		break;
	case SDL_PIXELFORMAT_RGB24:
		break;
	case SDL_PIXELFORMAT_BGR24:
		pSurface.reset(SDL_ConvertSurfaceFormat(pSurface.get(),
			SDL_PIXELFORMAT_RGB24, 0));
		break;
	default:
		throw std::runtime_error("Unsupported image pixel format at " + mapPath);
	}

	size_t length = size_t(pSurface->w);
	size_t width = size_t(pSurface->h);


	m_centerMap = glm::vec2((length / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE
							, (width / 2.f + MapSpace::SIZE_BORDER) * WallSpace::SIZE);

	// Order changed for optimization
	AddMiddleLevel(*pSurface);
	AddTopLevel(length, width);
	AddLowLevel(length, width);

	ComputeVisibleEdge(width);

	//m_labyrinth.BuildLabyrinth(GetWalls());
}

void CMap::ProcessRow(const Row & row, size_t widthCount, int level)
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
		Row row;
		for (size_t x = 0; x < (length + 2 * MapSpace::SIZE_BORDER); ++x)
		{		
			row.push_back(RecognizeSymbols[size_t(IdSymbol::Wall)]);
		}
		topLevel.push_back(row);
	}

	m_map.emplace_back(topLevel);
}

void CMap::AddMiddleLevel(SDL_Surface & surface)
{
	Level middleLevel;

	const auto rowSize = size_t(surface.w * surface.format->BytesPerPixel);
	std::vector<uint8_t> row(rowSize);

	for (size_t y = 0, height = size_t(surface.h); y < height; ++y)
	{
		auto *pixels = reinterpret_cast<uint8_t*>(surface.pixels);
		auto *upperRow = pixels + rowSize * y;

		std::memcpy(row.data(), upperRow, rowSize);
		
		middleLevel.push_back(row);
		AddBorderSymbolsForRow(middleLevel.back());
	}

	// Top border row
	middleLevel.insert(middleLevel.begin(), GenerateRowOfWalls(middleLevel.front()));
	// Low border row
	middleLevel.push_back(GenerateRowOfWalls(middleLevel.back()));

	m_map.push_back(middleLevel);
}

CMap::Row CMap::GenerateRowOfWalls(const CMap::Row & borderRow)
{
	Row result;
	for (size_t index = 1; index < (borderRow.size() - 1); ++index)
	{
		result.push_back(RecognizeSymbols[size_t(IdSymbol::Wall)]);	
	}
	// Border symbols
	result.insert(result.begin(), RecognizeSymbols[size_t(IdSymbol::Wall)]);
	result.insert(result.end(), RecognizeSymbols[size_t(IdSymbol::Wall)]);

	return result;
}

void CMap::AddBorderSymbolsForRow(Row & row)
{
	row.insert(row.begin(), RecognizeSymbols[size_t(IdSymbol::Wall)]);
	row.push_back(RecognizeSymbols[size_t(IdSymbol::Wall)]);
}

void CMap::AddLowLevel(size_t length, size_t width)
{
	Level lowLevel;

	for (size_t y = 0; y < (width + 2 * MapSpace::SIZE_BORDER); ++y)
	{
		Row row;
		for (size_t x = 0; x < (length + 2 * MapSpace::SIZE_BORDER); ++x)
		{
			row.push_back(RecognizeSymbols[size_t(IdSymbol::Wall)]);
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
		Row* row = nullptr;
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
	case int(NameLevels::Floor): case int(NameLevels::Ñeiling):
		return false;
	case int(NameLevels::Wall):
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

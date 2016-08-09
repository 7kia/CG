#include "stdafx.h"
#include "Map.h"

using namespace std;

CMap::CMap(const string & mapPath)
{
	CheckAndOpenFileForReading(mapPath);
	ReadMap(m_inputFile);
}

void CMap::ReadMap(ifstream & file)
{
	unsigned length = 0;
	unsigned width = 0;

	file >> length;
	file >> width;

	string inputString;
	getline(m_inputFile, inputString);// pass string
	while (getline(m_inputFile, inputString))
	{
		m_map.push_back(inputString);
	}

}

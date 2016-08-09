#pragma once

#include "../Mixin/HaveFileForReading.h"
#include <string>
#include <vector>

class CMap
	: public CHaveFileForReading
{
public:
	CMap(const std::string & mapPath);
	virtual ~CMap() = default;
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void	ReadMap(std::ifstream & file);
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<std::string> m_map;
};
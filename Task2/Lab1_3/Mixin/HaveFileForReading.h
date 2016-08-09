#pragma once

#include "FileProcess.h"

class CHaveFileForReading
{
public:
	CHaveFileForReading();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			CheckAndOpenFileForReading(const std::string& fileName);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::string		m_nameInputFile;
	std::ifstream	m_inputFile;
};
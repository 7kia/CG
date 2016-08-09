#pragma once

#include "FileProcess.h"

class CHaveFileForWriting
{
public:
	CHaveFileForWriting();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void			CheckAndOpenFileForWriting(const std::string& fileName);
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	std::string		m_nameOutputFile;
	std::fstream	m_outputFile;
};
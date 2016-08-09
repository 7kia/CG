#include "stdafx.h"
#include "HaveFileForWriting.h"

using namespace FileManagerSpace;
using namespace std;


CHaveFileForWriting::CHaveFileForWriting()
{
}

void CHaveFileForWriting::CheckAndOpenFileForWriting(const std::string & fileName)
{
	m_nameOutputFile = fileName;// TODO : see need m_nameInputFile
	 // close old file
	if (m_outputFile.is_open())
	{
		m_outputFile.close();
	}

	m_outputFile.open(fileName);
	m_outputFile.exceptions(ofstream::badbit);
	if (!m_outputFile.is_open())
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}
}

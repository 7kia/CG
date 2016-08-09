#include "stdafx.h"
#include "HaveFileForReading.h"

using namespace FileManagerSpace;
using namespace std;

CHaveFileForReading::CHaveFileForReading()
{
}

void CHaveFileForReading::CheckAndOpenFileForReading(const string & fileName)
{
	m_nameInputFile = fileName;// TODO : see need m_nameInputFile
	// close old file
	if (m_inputFile.is_open())
	{
		m_inputFile.close();
	}

	m_inputFile.open(fileName);
	//m_inputFile.exceptions(ifstream::badbit);
	if (!m_inputFile.is_open())
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

#pragma once

#include "ProgramContext\ProgramContext.h"

class CWaveProgramContext
: public CProgramContext
{
public:

	CWaveProgramContext();
//////////////////////////////////////////////////////////////////////
// Methods
	void					BindTextures() override;
	void					SetTexture() override;
	void					SetLights() override;
	void					SetAdditionalVariable() override;
//////////////////////////////////////////////////////////////////////
// Data
private:
	CTexture2DUniquePtr		m_pWaveTexture;
};

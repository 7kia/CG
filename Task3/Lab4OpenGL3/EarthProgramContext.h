#pragma once
#include "ProgramContext\ProgramContext.h"

class CEarthProgramContext
	: public CProgramContext
{
public:

    CEarthProgramContext();

	void			BindTextures() override;
	void			SetTexture() override;
	void			SetLights() override;

private:

    CTexture2DUniquePtr m_pEarthTexture;
    CTexture2DUniquePtr m_pCloudTexture;
    CTexture2DUniquePtr m_pNightTexture;
};

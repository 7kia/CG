#pragma once
#include "ProgramContext\ProgramContext.h"

class CEarthProgramContext
	: public CProgramContext
{
public:
    struct SLightSource
    {
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;
    };

    CEarthProgramContext();

    void Use() override;


    const SLightSource &GetLight0()const;

    void SetLight0(const SLightSource &source);

private:
    SLightSource m_light0;

    CTexture2DUniquePtr m_pEarthTexture;
    CTexture2DUniquePtr m_pCloudTexture;
    CTexture2DUniquePtr m_pNightTexture;
};

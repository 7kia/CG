#pragma once
#include "libchapter3.h"
#include "Mixin\IRenderer3D.h"

class CProgramContext;

class CEarthRenderer3D : public IRenderer3D
{
public:
    CEarthRenderer3D(CProgramContext &context);
    ~CEarthRenderer3D();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
    // IRenderer3D interface
    void					SetTexCoord2DOffset(size_t offset, size_t stride) override;
    void					SetPosition3DOffset(size_t offset, size_t stride) override;
    void					SetNormalOffset(size_t offset, size_t stride) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	CProgramContext			&m_context;
    CVertexAttribute		m_vertexAttr;
    CVertexAttribute		m_normalAttr;
    CVertexAttribute		m_texCoordAttr;
};

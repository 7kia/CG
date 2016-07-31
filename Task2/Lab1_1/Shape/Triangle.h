#pragma once

#include "IShape.h"
#include "../Mixin/TransparentShape.h"

class CTriangle final
	: public CTransparentShape
	, public IUpdatable
{
public:
	CTriangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetVertex(int index, const Vertex & value);
	Vertex					GetVertex(int index) const;
	std::array<Vertex, 3>	GetVertexes() const;

	static void				CheckIndex(int index);// TODO : see need transfer to other place
	//--------------------------------------------
	// CTransparentShape
	void					Update(float deltaTime) override final;
private:
	void					DrawOutputFaces() const override final;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::array<Vertex, 3>	m_vertex;
};

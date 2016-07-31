#pragma once

#include "../Shape/Shape.h"
#include <vector>

class IHaveVertex
{
public:
	virtual ~IHaveVertex() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void					SetVertex(int index, const Vertex & value) = 0;
	virtual Vertex					GetVertex(int index) const = 0;
	virtual std::vector<Vertex>		GetVertexes() const = 0;

	virtual void					CheckIndex(int index) const = 0;;// TODO : see need transfer to other place												  
};

class CHaveVertex : public IHaveVertex
{
public:
	CHaveVertex(size_t amountVertex);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void							SetVertex(int index, const Vertex & value) override final;
	Vertex							GetVertex(int index) const override final;
	std::vector<Vertex>				GetVertexes() const override final;

	void							CheckIndex(int index) const override final;;// TODO : see need transfer to other place												  
	// Data
protected:
	std::vector<Vertex>				m_vertex;
	size_t							m_amountVertex = 3;

};
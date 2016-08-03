#pragma once

#include "../Shape/Shape.h"
#include <vector>

typedef unsigned int uint;

class IHaveVertex
{
public:
	virtual ~IHaveVertex() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void					SetVertex(uint index, const Vertex & value) = 0;
	virtual Vertex					GetVertex(uint index) const = 0;
	virtual Vertex*					GetReferenceToVertex(int index) = 0;
	virtual std::vector<Vertex>		GetVertexes() const = 0;

	virtual void					CheckIndex(uint index) const = 0;;// TODO : see need transfer to other place												  
};

class CHaveThreeVertex : public IHaveVertex
{
public:
	CHaveThreeVertex();// TODO: delete parametr
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void							SetVertex(uint index, const Vertex & value) override final;
	Vertex							GetVertex(uint index) const override final;
	Vertex*							GetReferenceToVertex(int index) override final;;

	std::vector<Vertex>				GetVertexes() const override final;//

	void							CheckIndex(uint index) const override final;;// TODO : see need transfer to other place												  
	// Data
protected:
	std::vector<Vertex>				m_vertex;
};

class CHaveReferenceVertex : public IHaveVertex
{
public:
	CHaveReferenceVertex(size_t amountVertex);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void										SetVertex(uint index, const Vertex & value) override;
	Vertex										GetVertex(uint index) const override;
	Vertex*										GetReferenceToVertex(int index) override final;;

	std::vector<Vertex>							GetVertexes() const override final;//

	void										CheckIndex(uint index) const override final;// TODO : see need transfer to other place
protected:
	void										AddReferenceVertex(uint index, Vertex * value);
	virtual void								UpdateReference() {};// TODO : = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<std::vector<Vertex*>>			m_pVertex;
};
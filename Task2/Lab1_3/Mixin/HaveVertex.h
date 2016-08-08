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
	virtual void							SetVertex(uint index, const SVertexP3NT2 & value) = 0;
	virtual SVertexP3NT2					GetVertex(uint index) const = 0;
	virtual SVertexP3NT2*					GetReferenceToVertex(int index) = 0;
	virtual std::vector<SVertexP3NT2>		GetVertexes() const = 0;

	virtual void							SetPosition(uint index, const glm::vec3 & position) = 0;
	virtual glm::vec3						GetPosition(uint index) const = 0;

	virtual void							SetNoraml(uint index, const glm::vec3 & normal) = 0;
	virtual glm::vec3						GetNoraml(uint index) const = 0;

	virtual void							SetTexCoordinate(uint index, const glm::vec2 & texCoordinate) = 0;
	virtual glm::vec2						GetTexCoordinate(uint index) const = 0;


	virtual void					CheckIndex(uint index) const = 0;;// TODO : see need transfer to other place												  
};

class CHaveThreeVertex : public IHaveVertex
{
public:
	CHaveThreeVertex();// TODO: delete parametr
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void							SetVertex(uint index, const SVertexP3NT2 & value) override final;
	SVertexP3NT2					GetVertex(uint index) const override final;
	SVertexP3NT2*					GetReferenceToVertex(int index) override final;;

	std::vector<SVertexP3NT2>		GetVertexes() const override final;//


	void							SetPosition(uint index, const glm::vec3 & position);
	glm::vec3						GetPosition(uint index) const;

	void							SetNoraml(uint index, const glm::vec3 & normal);
	glm::vec3						GetNoraml(uint index) const;

	void							SetTexCoordinate(uint index, const glm::vec2 & texCoordinate);
	glm::vec2						GetTexCoordinate(uint index) const;



	void							CheckIndex(uint index) const override final;;// TODO : see need transfer to other place												  
	// Data
protected:
	std::vector<SVertexP3NT2>				m_vertex;
};

class CHaveReferenceVertex : public IHaveVertex
{
public:
	CHaveReferenceVertex(size_t amountVertex);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void										SetVertex(uint index, const SVertexP3NT2 & value) override;
	SVertexP3NT2								GetVertex(uint index) const override;
	SVertexP3NT2*								GetReferenceToVertex(int index) override final;;

	std::vector<SVertexP3NT2>					GetVertexes() const override final;//

	void										CheckIndex(uint index) const override final;// TODO : see need transfer to other place
protected:
	void										AddReferenceVertex(uint index, SVertexP3NT2 * value);
	virtual void								UpdateReference() {};// TODO : = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<std::vector<SVertexP3NT2*>>			m_pVertex;
};
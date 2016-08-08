#pragma once

#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

typedef unsigned int uint;

// Вершина с трёхмерной позицией, нормалью и 2D координатами текстуры.
struct SVertexP3NT2
{
	SVertexP3NT2() = default;
	SVertexP3NT2(const glm::vec3 & position
		, const glm::vec2 & texCoord
		, const glm::vec3 & normal);

	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

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


	virtual void							CheckVertexIndex(uint index) const = 0;;// TODO : see need transfer to other place												  
};

class CHaveVertexes : public IHaveVertex
{
public:
	CHaveVertexes();// TODO: delete parametr
	CHaveVertexes(uint size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void							SetVertex(uint index, const SVertexP3NT2 & value) override final;
	SVertexP3NT2					GetVertex(uint index) const override final;
	SVertexP3NT2*					GetReferenceToVertex(int index) override final;;

	std::vector<SVertexP3NT2>		GetVertexes() const override final;//


	void							SetPosition(uint index, const glm::vec3 & position) override final;
	glm::vec3						GetPosition(uint index) const override final;

	void							SetNoraml(uint index, const glm::vec3 & normal) override final;
	glm::vec3						GetNoraml(uint index) const override final;

	void							SetTexCoordinate(uint index, const glm::vec2 & texCoordinate) override final;
	glm::vec2						GetTexCoordinate(uint index) const override final;



	void							CheckVertexIndex(uint index) const override final;// TODO : see need transfer to other place												  
	// Data
protected:
	std::vector<SVertexP3NT2>		m_vertices;
	std::vector<uint32_t>			m_indicies;

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
	SVertexP3NT2*								GetReferenceToVertex(int index) override final;

	std::vector<SVertexP3NT2>					GetVertexes() const override final;//

	void										SetPosition(uint index, const glm::vec3 & position) override final;
	glm::vec3									GetPosition(uint index) const override final;

	void										SetNoraml(uint index, const glm::vec3 & normal) override final;
	glm::vec3									GetNoraml(uint index) const override final;

	void										SetTexCoordinate(uint index, const glm::vec2 & texCoordinate) override final;
	glm::vec2									GetTexCoordinate(uint index) const override final;


	void										CheckVertexIndex(uint index) const override final;// TODO : see need transfer to other place
protected:
	void										AddReferenceVertex(uint index, SVertexP3NT2 * value);
	virtual void								UpdateReference() {};// TODO : = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<std::vector<SVertexP3NT2*>>			m_pVertex;
};
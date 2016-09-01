#pragma once

#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

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
	virtual void							SetVertex(size_t index, const SVertexP3NT2 & value) = 0;
	virtual SVertexP3NT2					GetVertex(size_t index) const = 0;
	virtual SVertexP3NT2*					GetReferenceToVertex(int index) = 0;

	virtual std::vector<SVertexP3NT2>		GetSourceVertexes() const = 0;
	virtual std::vector<SVertexP3NT2>		GetVertexes() const = 0;

	virtual void							SetSourceVertexPosition(size_t index, const glm::vec3 & position) = 0;
	virtual glm::vec3						GetSourceVertexPosition(size_t index) const = 0;

	//virtual void							SetVertexPosition(size_t index, const glm::vec3 & position) = 0;
	virtual glm::vec3						GetVertexPosition(size_t index) const = 0;

	virtual void							SetVertexNormal(size_t index, const glm::vec3 & normal) = 0;
	virtual glm::vec3						GetVertexNormal(size_t index) const = 0;

	virtual	void							UpdateNormals() {};

	virtual void							SetVertexTexCoordinate(size_t index, const glm::vec2 & texCoordinate) = 0;
	virtual glm::vec2						GetVertexTexCoordinate(size_t index) const = 0;

	virtual void							SetIndex(size_t index, uint32_t newIndex) = 0;
	virtual uint32_t						GetIndex(size_t index) const = 0;

	virtual void							CheckVertexIndex(size_t index) const = 0;;	
	virtual void							CheckIdIndex(size_t index) const = 0;;											  

};

class CHaveVertexes : public IHaveVertex
{
public:
	CHaveVertexes();
	CHaveVertexes(size_t size);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void							ResizeVertexArray(size_t newSize);
	size_t							GetAmountVertexes() const;

	void							ResizeIndexArray(size_t newSize);
	size_t							GetAmountVIndexes() const;

	void							SetVertex(size_t index, const SVertexP3NT2 & value) override final;
	SVertexP3NT2					GetVertex(size_t index) const override final;
	SVertexP3NT2*					GetReferenceToVertex(int index) override final;

	std::vector<SVertexP3NT2>		GetSourceVertexes() const override final;
	std::vector<uint32_t>			GetIndexes() const;

	void							SetSourceVertexPosition(size_t index, const glm::vec3 & position) override final;
	glm::vec3						GetSourceVertexPosition(size_t index) const override final;

	void							SetVertexNormal(size_t index, const glm::vec3 & normal) override final;
	glm::vec3						GetVertexNormal(size_t index) const override final;

	void							SetVertexTexCoordinate(size_t index, const glm::vec2 & texCoordinate) override final;
	glm::vec2						GetVertexTexCoordinate(size_t index) const override final;

	void							SetIndex(size_t index, uint32_t newIndex) override final;
	uint32_t						GetIndex(size_t index) const override final;


	void							CheckVertexIndex(size_t index) const override final;	
	void							CheckIdIndex(size_t index) const override final;											  

//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<SVertexP3NT2>		m_vertices;
	std::vector<uint32_t>			m_indicies;

};
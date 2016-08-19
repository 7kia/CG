#include "stdafx.h"
#include "3DShape.h"

I3DShape::I3DShape()
	: IDrawable()
{
}

CIdentity3DShape::CIdentity3DShape()
	: C3DShape()
	, CHaveVertexes()

{
}

void CIdentity3DShape::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));

	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});

	glPopMatrix();
}

std::vector<SVertexP3NT2> CIdentity3DShape::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for //(const auto & index : m_indicies)
		(size_t index = 0; index < m_vertices.size(); ++index)
	{
		auto vertexWithTransform = m_vertices[index];
		vertexWithTransform.position = GetVertexPosition(index);
		result.push_back(vertexWithTransform);
	}
	return result;
}

glm::vec3 CIdentity3DShape::GetVertexPosition(uint index) const
{
	CheckVertexIndex(index);

	auto currentPosition = glm::translate(GetTransform(), m_vertices[index].position);
	return glm::vec3(currentPosition[3][0], currentPosition[3][1], currentPosition[3][2]);
}



C3DShape::C3DShape()
	: I3DShape()
	, CTransformable()
{
}

IdentityShapeSharedPtr Weld(const IdentityShapeSharedPtr first
							, const IdentityShapeSharedPtr second
							, size_t firstIndex
							, size_t secondIndex)
{
	IdentityShapeSharedPtr result = std::make_shared<CIdentity3DShape>();
	size_t amountVertexInFirst = first->GetAmountVertexes();
	size_t amountVertexInSecond = second->GetAmountVertexes();
	size_t amountIndexesInFirst = first->GetAmountVIndexes();
	size_t amountIndexesInSecond = second->GetAmountVIndexes();

	result->ResizeVertexArray(amountVertexInFirst + amountVertexInSecond - 1);
	result->ResizeIndexArray(amountIndexesInFirst + amountIndexesInSecond);
	
	// ���������� ������ ������
	for (size_t index = 0; index < amountVertexInFirst; ++index)
	{
		result->SetVertex(index, first->GetVertex(index));
	}
	for (size_t index = 0; index < amountIndexesInFirst; ++index)
	{
		result->SetIndex(index, first->GetIndex(index));
	}

	// ����� ������� ���������� ����� �� ���������
	auto indexes = result->GetIndexes();
	size_t maxIndex = *std::max_element(indexes.begin(), indexes.end());
	
	// ������� ������� � � ������
	auto vertexesFromSecond = second->GetVertexes();
	auto indexesFromSecond = second->GetIndexes();

	vertexesFromSecond.erase(vertexesFromSecond.begin() + secondIndex);
	// ������ ������� �� ������
	/*
		std::replace_if(indexesFromSecond.begin()
					, indexesFromSecond.end()
					, [&](uint32_t index)
						{
							return index == secondIndex;
						}
					, firstIndex);
	*/


	auto GetNewIndex = [amountIndexesInFirst](size_t oldIndex)
	{
		return oldIndex + amountIndexesInFirst;
	};
	boost::transform(indexesFromSecond, indexesFromSecond.begin(), GetNewIndex);

	///////////////////
	// ������ �� ������ ������
	for (size_t index = amountVertexInFirst; index < result->GetAmountVertexes(); ++index)
	{
		result->SetVertex(index, second->GetVertex(index - amountVertexInFirst));
	}
	for (size_t index = amountIndexesInFirst; index < result->GetAmountVIndexes(); ++index)
	{
		result->SetIndex(index, indexesFromSecond[index - amountIndexesInFirst]);
	}

	// ������ �������
	for (size_t index = amountIndexesInFirst; index < result->GetAmountVIndexes(); ++index)
	{
		if (result->GetIndex(index) == (secondIndex + maxIndex + 1))
		{
			result->SetIndex(index, firstIndex);
		}
	}

	return result;
}

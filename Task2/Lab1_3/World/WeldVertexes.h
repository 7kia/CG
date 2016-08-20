#pragma once

#include "../3DShape/3DShape.h"

// this version create new shape
IdentityShapeSharedPtr Weld(const IdentityShapeSharedPtr first
	, const IdentityShapeSharedPtr second
	, std::vector<std::pair<size_t, size_t>> indexesVertex);

// change first, second is not changed
bool					WeldToFirst(CIdentity3DShape* first
	, const CIdentity3DShape* second
	, std::vector<std::pair<size_t, size_t>> indexesVertex);

VectorPairsIndexes FindCommonVertexes(const IdentityShapeSharedPtr first
	, const IdentityShapeSharedPtr second);
VectorPairsIndexes FindCommonVertexes(const std::vector<SVertexP3NT2> & first
	, const std::vector<SVertexP3NT2> & second);

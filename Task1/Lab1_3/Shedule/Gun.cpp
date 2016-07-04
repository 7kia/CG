#include "stdafx.h"
#include "Gun.h"

CGun::CGun()
	: CStaticShape()
{
	auto pCircle = std::make_shared<CBall>();
	m_components.push_back(pCircle);

	auto pTrunk = std::make_shared<CRectangle>();
	pTrunk->SetWidth(15.f);
	pTrunk->SetHeight(50.f);

	m_components.push_back(pTrunk);
}

CGun::~CGun()
{
}

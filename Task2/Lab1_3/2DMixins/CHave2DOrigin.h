#pragma once

#include "CHave2DPosition.h"

class IHave2DOrigin
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual ~IHave2DOrigin() = default;

	virtual void				SetReferenceSystemOrigin(const glm::vec2 & origin) = 0;
	virtual glm::vec2			GetReferenceSystemOrigin() const = 0;

	virtual void				SetOrigin(const glm::vec2 & origin) = 0;
	virtual glm::vec2			GetOrigin() const = 0;
	//////////////////////////////////////////////////////////////////////
};

class CHave2DOrigin
	: public IHave2DOrigin
{
public:
	CHave2DOrigin();
	virtual ~CHave2DOrigin() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void				SetReferenceSystemOrigin(const glm::vec2 & origin) override;
	glm::vec2			GetReferenceSystemOrigin() const override;

	void				SetOrigin(const glm::vec2 & origin) override;
	glm::vec2			GetOrigin() const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2			m_referenceSystemOrigin;
	glm::vec2			m_shapeOrigin;
};

//////////////////////////////////////////////////////////////////////
// Have GetCenterPosition() , which give world position
//////////////////////////////////////////////////////////////////////
class CHavePositionAndOrigin
	: public CHave2DOrigin
	, public CHave2DPosition
{
public:
	CHavePositionAndOrigin();
	virtual ~CHavePositionAndOrigin() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	glm::vec2	GetCenterPosition(const glm::vec2 & origin) const;
	glm::vec2	GetCenterPosition() const;
};
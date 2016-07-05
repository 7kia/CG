#pragma once

#include <glm/vec2.hpp>

class IHavePosition
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual ~IHavePosition() = default;

	virtual void				SetPosition(const glm::vec2 & position) { (void)position;  };
	virtual void				SetPosition(float x, float y) { (void)x; (void)y; };
	virtual glm::vec2			GetPosition() const {};

	virtual glm::vec2			GetCenterPosition(const glm::vec2 & origin) const { (void)origin; };
	virtual glm::vec2			GetCenterPosition() const {} ;

	virtual void				SetReferenceSystemOrigin(const glm::vec2 & origin) { (void)origin; };
	virtual glm::vec2			GetReferenceSystemOrigin() const {};

	virtual void				SetShapeOrigin(const glm::vec2 & origin) { (void)origin; };
	virtual glm::vec2			GetShapeOrigin() const {};

//////////////////////////////////////////////////////////////////////
};

class CHavePosition
	: public IHavePosition
{
public:
	CHavePosition();
	virtual ~CHavePosition() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:

	// these methods not need, will define heir have body(this have position)
	//void				SetPosition(const glm::vec2 & position);
	//void				SetPosition(float x, float y);
	//glm::vec2			GetPosition() const;

	//glm::vec2			GetCenterPosition(const glm::vec2 & origin) const override;
	//glm::vec2			GetCenterPosition() const override;

	void				SetReferenceSystemOrigin(const glm::vec2 & origin) override;
	glm::vec2			GetReferenceSystemOrigin() const override;

	void				SetShapeOrigin(const glm::vec2 & origin) override;
	glm::vec2			GetShapeOrigin() const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2			m_referenceSystemOrigin;
	glm::vec2			m_shapeOrigin;
//////////////////////////////////////////////////////////////////////
};
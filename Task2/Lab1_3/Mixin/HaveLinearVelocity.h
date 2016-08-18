#pragma once

class CHaveLinearVelocity
{
public:
	CHaveLinearVelocity(float velocity);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	enum class DirectionWalk
	{
		  None = 0
		, Back
		, Forward
	};

	void	SetMaxLinearVelocity(float velocity);
	float	GetMaxLinearVelocity() const;

	void	SetMaxSpeedUpTime(float time);
	float	GetMaxSpeedUpTime() const;

	void	SetMinSpeedUpTime(float velocity);
	float	GetMinSpeedUpTime() const;


	float	GetCurrentLinearVelocity(float deltaTime);

	void	ResetCurrentLinearVelocity();

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	float			m_maxLinearVelocity = 0.f;
	float	 		m_maxSpeedUpTime = 3.f;
	float			m_minSpeedUpTime = 0.25f;

	float			m_currentSpeedUpTime = 0.f;
	float			m_currentVelocity = 0.f;
	DirectionWalk	m_directionWalk = DirectionWalk::None;
};
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

	void	SetMaxTime(float time);
	float	GetMaxTime() const;

	void	SetMinTime(float velocity);
	float	GetMinTime() const;


	float	GetCurrentLinearVelocity(float deltaTime);

	void	ResetCurrentLinearVelocity();

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	float			m_maxLinearVelocity = 0.f;
	float	 		m_maxTime = 3.f;// TODO : fix name
	float			m_minTime = 0.25f;// TODO : fix name

	float			m_currentTime = 0.f;
	float			m_currentVelocity = 0.f;
	DirectionWalk	m_directionWalk = DirectionWalk::None;
};
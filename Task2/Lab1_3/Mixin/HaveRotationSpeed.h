#pragma once

class CHaveRotationSpeed
{
public:
	CHaveRotationSpeed(float rotation);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	enum class DirectionRotation
	{
		  None = 0
		, Left
		, Right
	};
	void	SetMaxRotationSpeed(float rotation);
	float	GetMaxRotationSpeed() const;

	void	SetMaxRotationUpTime(float time);
	float	GetMaxRotationUpTime() const;

	void	SetMinRotationUpTime(float time);
	float	GetMinRotationUpTime() const;


	float	GetCurrentRotationSpeed(float deltaTime);

	void	ResetCurrentRotationSpeed();

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	float				m_maxRotationSpeed = 0.f;
	float	 			m_maxRotationUpTime = 1.5f;
	float				m_minRotationUpTime = 0.25f;

	float				m_currentRotationUpTime = 0.f;
	float				m_currentRotation = 0.f;
	DirectionRotation	m_directionRotation = DirectionRotation::None;
};
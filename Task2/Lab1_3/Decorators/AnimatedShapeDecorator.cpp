#include "stdafx.h"
#include "AnimatedShapeDecorator.h"


void CAnimatedShapeDecorator::Update(float deltaTime)
{
	// Вычисляем фазу анимации по времени на отрезке [0..1].
	m_animationPhase += (deltaTime / ANIMATION_STEP_SECONDS);
	if (m_animationPhase >= 1)
	{
		m_animationPhase = 0;
		switch (m_animation)
		{
		case Rotating:
			m_animation = Pulse;
			break;
		case Pulse:
			m_animation = Bounce;
			break;
		case Bounce:
			m_animation = Rotating;
			break;
		}
	}
	CAbstractShapeDecorator::Update(deltaTime);
}

void CAnimatedShapeDecorator::Draw() const
{
	const glm::mat4 matrix = GetAnimationTransform();
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(matrix));
	m_pChild->Draw();
	glPopMatrix();
}


// Документация по функциям для модификации матриц:
// http://glm.g-truc.net/0.9.2/api/a00245.html
glm::mat4 CAnimatedShapeDecorator::GetAnimationTransform() const
{
	switch (m_animation)
	{
	case Rotating:
		return GetRotateZTransfrom(m_animationPhase);
	case Pulse:
		return GetScalingPulseTransform(m_animationPhase);
	case Bounce:
		return GetBounceTransform(m_animationPhase);
	}
	// Недостижимый код - вернём единичную матрицу.
	return glm::mat4();
}

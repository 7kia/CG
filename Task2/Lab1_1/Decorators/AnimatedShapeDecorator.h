#pragma once

#include "AbstractShapeDecorator.h"

namespace
{
	const float ANIMATION_STEP_SECONDS = 2.f;

	/// @param phase - Фаза анимации на отрезке [0..1]
	glm::mat4 GetRotateZTransfrom(float phase)
	{
		// угол вращения вокруг оси Z лежит в отрезке [0...2*pi].
		const float angle = float(2 * M_PI) * phase;

		return glm::rotate(glm::mat4(), angle, { 0, 0, 1 });
	}

	/// @param phase - Фаза анимации на отрезке [0..1]
	glm::mat4 GetScalingPulseTransform(float phase)
	{
		// число пульсаций размера - произвольная константа.
		const int pulseCount = 4;
		float scale = fabsf(cosf(float(pulseCount * M_PI) * phase));

		return glm::scale(glm::mat4(), { scale, scale, scale });
	}

	/// @param phase - Фаза анимации на отрезке [0..1]
	glm::mat4 GetBounceTransform(float phase)
	{
		// начальная скорость и число отскоков - произвольные константы.
		const int bounceCount = 4;
		const float startSpeed = 15.f;
		// "время" пробегает bounceCount раз по отрезку [0...1/bounceCount].
		const float time = fmodf(phase, 1.f / float(bounceCount));
		// ускорение подбирается так, чтобы на 0.25с скорость стала
		// противоположна начальной.
		const float acceleration = -(startSpeed * 2.f * float(bounceCount));
		// расстояние - результат интегрирования функции скорости:
		//  speed = startSpeed + acceleration * time;
		float offset = time * (startSpeed + 0.5f * acceleration * time);

		// для отскоков с нечётным номером меняем знак.
		const int bounceNo = int(phase * bounceCount);
		if (bounceNo % 2)
		{
			offset = -offset;
		}

		return glm::translate(glm::mat4(), { offset, 0.f, 0.f });
	}
}

class CAnimatedShapeDecorator : public CAbstractShapeDecorator
{

//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void			Update(float deltaTime);
	void			Draw()const;
	//--------------------------------------------
private:
	enum Animation
	{
		Rotating,
		Pulse,
		Bounce,
	};

	glm::mat4		GetAnimationTransform() const;
//////////////////////////////////////////////////////////////////////
// Methods
private:
	Animation		m_animation = Rotating;
	float			m_animationPhase = 0;
};
#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#pragma push_macro("_MSC_EXTENSIONS")
#undef _MSC_EXTENSIONS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma pop_macro("_MSC_EXTENSIONS")

#include <SDL2/SDL_events.h>

#include <chrono>
#include <type_traits>
#include <iostream>
#include <mutex>
#include <exception>
#include <array>
#include <memory>
#include <vector>

#include <Box2D/Box2D.h>

// TODO : transfer to other place
template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

float ToDegree(float radian);

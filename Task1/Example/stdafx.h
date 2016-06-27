#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <SDL2/SDL_rect.h>// TODO : ask why if there sdl2/sdl.h then error with sdl_main8
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/noncopyable.hpp>


#include <chrono>
#include <type_traits>
#include <iostream>
#include <mutex>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>

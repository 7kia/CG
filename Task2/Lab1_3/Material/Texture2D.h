#pragma once
#include <boost/noncopyable.hpp>
#include <boost/scope_exit.hpp>
#include <string>
#include <memory>

class CTexture2D : private boost::noncopyable
{
public:
    CTexture2D();
    ~CTexture2D();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			Bind() const;
    static void		Unbind();

	void			SetIndex(unsigned int index);
	unsigned		GetIndex() const;

    template <class TFunction>
    void DoWhileBinded(TFunction && fn)
    {
        Bind();
        // При выходе из функции надо обязательно сделать Unbind.
		// remove because was warnigns
		//BOOST_SCOPE_EXIT_ALL() {
		//	Unbind();
		//};

        fn();
		Unbind();
	
    }
//////////////////////////////////////////////////////////////////////
// Data
private:
    unsigned m_textureId = 0;
};

using CTexture2DSharedPtr = std::shared_ptr<CTexture2D>;

// Используем unique_ptr с явно заданной функцией удаления вместо delete.
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>;
using SDLPixelFormatPtr = std::unique_ptr<SDL_PixelFormat, void(*)(SDL_PixelFormat*)>;

CTexture2DSharedPtr LoadTexture2DFromBMP(const std::string &path);

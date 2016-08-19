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
       
		// TODO : see need it
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

using CTexture2DSharedPtr = std::shared_ptr<CTexture2D>;// TODO : see might need unique_ptr

CTexture2DSharedPtr LoadTexture2DFromBMP(const std::string &path);

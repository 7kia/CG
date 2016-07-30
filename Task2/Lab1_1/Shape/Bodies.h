#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glu.h>
#include <boost/noncopyable.hpp>


#include "IShape.h"
#include "Cube.h"
#include "Tetrahedron.h"



class CSphereQuadric final
        : public IShape
        , private boost::noncopyable
		, public CHaveFaceColor
{
public:
    CSphereQuadric();
    ~CSphereQuadric();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	//void Update(float) override final;
    void Draw()const override final;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
    GLUquadric *m_quadric = nullptr;
};

class CConoidQuadric final
        : public IShape
        , private boost::noncopyable
		, public CHaveFaceColor
{
public:
    CConoidQuadric();
    ~CConoidQuadric();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
    void			Update(float) final {}
    void			Draw()const final;
	//--------------------------------------------

    /// @param value - in range [0..1]
    void			SetTopRadius(double value);
    //void			SetColor(const glm::vec3 &color);
//////////////////////////////////////////////////////////////////////
// Data
private:
    GLUquadric*		m_quadric = nullptr;
    double			m_topRadius = 1.;
};

#pragma once
#include "DispatchEvent.h"
#include "Shedule/Shedule.h"
#include "Shape/Rectangle.h"

#include "Shedule/PhysicalSystem.h"

#include <vector>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGTH = 600;


class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();
//////////////////////////////////////////////////////////////////////
// Methods
protected:
	//--------------------------------------------
    // CAbstractWindow interface
    void									OnUpdateWindow(float deltaSeconds) override;
    void									OnDrawWindow(const glm::ivec2 &size) override;
	//--------------------------------------------
    // IInputEventAcceptor interface
    void									OnDragBegin(const glm::vec2 &pos) override;
    void									OnDragMotion(const glm::vec2 &pos) override;
    void									OnDragEnd(const glm::vec2 &pos) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	void									SetupView(const glm::ivec2 &size);
//////////////////////////////////////////////////////////////////////
// Methods
private:
    CShedule								m_shedule;

    glm::vec2								m_dragOffset;
//////////////////////////////////////////////////////////////////////
};

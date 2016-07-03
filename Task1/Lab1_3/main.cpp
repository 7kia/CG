#include "stdafx.h"
#include "Window.h"

int main()
{
    glewInit();

    CWindow window;
    window.Show({WINDOW_WIDTH, WINDOW_HEIGTH});
    window.DoGameLoop();

	return 0;
}

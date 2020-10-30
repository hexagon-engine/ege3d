#include <ege3d/window/Window.h>
#include <ege3d/window/WindowSettings.h>

int main()
{
    EGE3d::Window window;
    window.create(300, 300, "EGE3d Test", EGE3d::WindowSettings()
                  .setBackgroundColor(255)
                  .setForegroundColor(0));

    while(window.isOpen())
        window.dispatchEvents();

    window.close();
    return 0;
}
